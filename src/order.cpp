
#include "../include/order.hpp"
#include <stdexcept>
#include <curl/curl.h>
#include <iostream>
#include <sstream>

DeribitOrder::DeribitOrder(DeribitAuth& auth_instance) : auth(auth_instance) {
    if (!auth.isAuthenticated()) {
        throw std::runtime_error("Authentication required before placing orders");
    }
}

std::string DeribitOrder::makeAuthenticatedPostRequest(const std::string& endpoint, const std::string& payload) {
    if (!auth.isAuthenticated()) {
        if (!auth.authenticate()) {
            throw std::runtime_error("Failed to authenticate");
        }
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }

    std::string response;
    std::string url = "https://test.deribit.com/api/v2/" + endpoint;

    struct curl_slist* headers = nullptr;
    std::string auth_header = "Authorization: Bearer " + auth.getAccessToken();
    headers = curl_slist_append(headers, auth_header.c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DeribitAuth::WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error("Request failed: " + std::string(curl_easy_strerror(res)));
    }

    return response;
}

std::string DeribitOrder::placeBuyOrder(const std::string& instrument, const std::string& type, int quantity, double price) {
    // Construct JSON payload
    std::ostringstream payload;
    payload << "{\"jsonrpc\":\"2.0\",\"method\":\"private/buy\",\"id\":1,\"params\":{";
    payload << "\"instrument_name\":\"" << instrument << "\",";
    payload << "\"amount\":" << quantity << ",";
    payload << "\"type\":\"" << type << "\"";
    
    if (type == "limit" && price > 0) {
        payload << ",\"price\":" << price;
    }
    
    payload << "}}";

    return makeAuthenticatedPostRequest("", payload.str());
}
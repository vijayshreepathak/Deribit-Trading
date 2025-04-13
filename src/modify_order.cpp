#include "modify_order.hpp"
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>

ModifyOrder::ModifyOrder(const std::string& api_key, const std::string& api_secret)
    : api_key_(api_key), api_secret_(api_secret) {}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool ModifyOrder::getAccessToken() {
    CURL* curl;
    CURLcode res;
    struct curl_slist* headers = NULL;
    std::string response_string;

    // Prepare the URL for the authentication request
       const std::string url = "https://test.deribit.com/api/v2/public/auth";
    const std::string post_fields = "grant_type=client_credentials&client_id=" + api_key_ + "&client_secret=" + api_secret_;
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set up the headers for the request
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        // Set the URL and POST data
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        // Perform the request
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Curl request failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

          // DEBUG: Print response to see if it's formatted correctly
        std::cout << "Auth Response: " << response_string << std::endl;

        // Here we parse the response to extract the access token
         size_t token_pos = response_string.find("\"access_token\":\"");
        if (token_pos != std::string::npos) {
            size_t start = token_pos + 16;
            size_t end = response_string.find("\"", start);
            access_token_ = response_string.substr(start, end - start);
        }

        if (access_token_.empty()) {
            std::cerr << "Failed to parse access token from response" << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        std::cout << "Access token obtained successfully" << std::endl;

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return true;
    }

    return false;
}

bool ModifyOrder::sendModifyRequest(const std::string& order_id, double price, int quantity) {
    CURL* curl;
    CURLcode res;
    struct curl_slist* headers = NULL;
    std::string response_string;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Add headers for authentication and content-type
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        // Authorization header
        std::string auth_header = "Authorization: Bearer " + access_token_;
        headers = curl_slist_append(headers, auth_header.c_str());

        // Prepare the data for modifying the order
        std::string data = "order_id=" + order_id + "&price=" + std::to_string(price) + "&quantity=" + std::to_string(quantity);

        // Set the URL for the modify order request
        curl_easy_setopt(curl, CURLOPT_URL, "https://test.deribit.com/api/v1/private/edit");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Curl request failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        // You can check the response if needed
        std::cout << "Response: " << response_string << std::endl;

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return true;
    }

    return false;
}

bool ModifyOrder::modifyOrder(const std::string& order_id, double price, int quantity) {
    // First, obtain the access token
    if (!getAccessToken()) {
        std::cerr << "Failed to get access token" << std::endl;
        return false;
    }

    // Then, send the modify request
    return sendModifyRequest(order_id, price, quantity);
}

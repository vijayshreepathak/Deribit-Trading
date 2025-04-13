#include "../include/account.hpp"
#include <stdexcept>
#include <iostream>

DeribitAccount::DeribitAccount(DeribitAuth& auth_instance) : auth(auth_instance) {
    if (!auth.isAuthenticated()) {
        throw std::runtime_error("Authentication required before accessing account information");
    }
}

std::string DeribitAccount::makeAuthenticatedRequest(const std::string& endpoint) {
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

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DeribitAuth::WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error("Request failed: " + std::string(curl_easy_strerror(res)));
    }

    return response ;
}

std::string DeribitAccount::getAccountSummary() {
    return makeAuthenticatedRequest("private/get_account_summary?currency=BTC");
}
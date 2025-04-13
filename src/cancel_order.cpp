#include "cancel_order.hpp"
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

CancelOrder::CancelOrder(const std::string& api_key, const std::string& api_secret)
    : api_key_(api_key), api_secret_(api_secret) {}

bool CancelOrder::getAccessToken() {
    CURL* curl;
    CURLcode res;
    struct curl_slist* headers = NULL;

    // Prepare the URL for the authentication request
    const std::string url = "https://test.deribit.com/api/v2/public/auth";
    const std::string post_fields = "client_id=" + api_key_ + "&client_secret=" + api_secret_ + "&grant_type=client_credentials";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set up the headers for the request
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        // Set the URL and POST data
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        // Perform the request
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Curl request failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        // Extract the access token from the response
        char* response;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);
        std::cout << "Access token obtained successfully" << std::endl;

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return true;
    }

    return false;
}

bool CancelOrder::sendCancelRequest(const std::string& order_id) {
    CURL* curl;
    CURLcode res;
    struct curl_slist* headers = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Add headers for authentication and content-type
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        std::string auth_header = "Authorization: Bearer " + access_token_;
        headers = curl_slist_append(headers, auth_header.c_str());

        // Prepare the data for the cancel order request
        std::string data = "order_id=" + order_id;

        // Set the URL for the cancel order request
        curl_easy_setopt(curl, CURLOPT_URL, "https://test.deribit.com/api/v1/private/cancel");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Curl request failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        std::cout << "Order cancellation request sent successfully" << std::endl;

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return true;
    }

    return false;
}

bool CancelOrder::cancelOrder(const std::string& order_id) {
    // First, obtain the access token
    if (!getAccessToken()) {
        std::cerr << "Failed to get access token" << std::endl;
        return false;
    }

    // Then, send the cancel request
    return sendCancelRequest(order_id);
}

#include "get_orderbook.hpp"
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <json/json.h>

GetOrderBook::GetOrderBook(const std::string& api_key, const std::string& api_secret)
    : api_key_(api_key), api_secret_(api_secret) {}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool GetOrderBook::getAccessToken() {
    CURL* curl;
    CURLcode res;
    struct curl_slist* headers = NULL;
    std::string response_string;

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

        // Parse the JSON response
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(response_string, root);
        
        if (!parsingSuccessful) {
            std::cerr << "Failed to parse JSON response: " << reader.getFormattedErrorMessages() << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        // Extract the access token
        if (root.isMember("result") && root["result"].isMember("access_token")) {
            access_token_ = root["result"]["access_token"].asString();
            std::cout << "Access token obtained successfully" << std::endl;
        } else {
            std::cerr << "Failed to extract access token from response" << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return true;
    }

    return false;
}

bool GetOrderBook::sendHttpRequest(const std::string& instrument) {
    CURL* curl;
    CURLcode res;
    struct curl_slist* headers = NULL;
    std::string response_string;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        std::string auth_header = "Authorization: Bearer " + access_token_;
        headers = curl_slist_append(headers, auth_header.c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        std::string url = "https://test.deribit.com/api/v1/public/getorderbook?instrument_name=" + instrument;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Curl request failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        std::cout << "Order book (HTTP response): " << response_string << std::endl;

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return true;
    }

    return false;
}

bool GetOrderBook::getOrderBook(const std::string& instrument) {
    // First, obtain the access token
    if (!getAccessToken()) {
        std::cerr << "Failed to get access token" << std::endl;
        return false;
    }

    // Then, send the HTTP request
    return sendHttpRequest(instrument);
}

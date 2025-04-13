#include "../include/auth.hpp"
#include <iostream>

size_t DeribitAuth::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

DeribitAuth::DeribitAuth(const std::string& key, const std::string& secret) 
    : api_key(key), api_secret(secret), is_authenticated(false) {
    curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }
}

DeribitAuth::~DeribitAuth() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

std::string DeribitAuth::makeRequest(const std::string& endpoint, const std::string& params) {
    if (!curl) {
        throw std::runtime_error("CURL not initialized");
    }

    std::string url = "https://test.deribit.com/api/v2/" + endpoint + "?" + params;
    std::string response;

      // Print URL for debugging (remove sensitive data)
    std::cout << "Making request to: " << endpoint << std::endl;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

       // Add verbose debug output
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
    }

     // Print response for debugging (be careful not to expose sensitive data)
    std::cout << "Response received. Length: " << response.length() << std::endl;
    std::cout << "Response preview: " << response.substr(0, 100) << "..." << std::endl;

    return response;
}

std::string DeribitAuth::extractToken(const std::string& json_response, const std::string& token_key) {
    // Simple JSON parsing to extract token
    size_t pos = json_response.find("\"" + token_key + "\"");
    if (pos == std::string::npos) return "";
    
    pos = json_response.find("\"", pos + token_key.length() + 2);
    if (pos == std::string::npos) return "";
    
    size_t end_pos = json_response.find("\"", pos + 1);
    if (end_pos == std::string::npos) return "";
    
    return json_response.substr(pos + 1, end_pos - pos - 1);
}

bool DeribitAuth::authenticate() {
    try {
        std::string params = "client_id=" + api_key + "&client_secret=" + api_secret + "&grant_type=client_credentials";
        std::string response = makeRequest("public/auth", params);

        access_token = extractToken(response, "access_token");
        refresh_token = extractToken(response, "refresh_token");

        is_authenticated = !access_token.empty();
        return is_authenticated;
    }
    catch (const std::exception& e) {
        std::cerr << "Authentication failed: " << e.what() << std::endl;
        return false;
    }
}

bool DeribitAuth::refreshAccessToken() {
    if (refresh_token.empty()) {
        return false;
    }

    try {
        std::string params = "refresh_token=" + refresh_token;
        std::string response = makeRequest("public/auth", params);

        std::string new_access_token = extractToken(response, "access_token");
        std::string new_refresh_token = extractToken(response, "refresh_token");

        if (!new_access_token.empty()) {
            access_token = new_access_token;
            refresh_token = new_refresh_token;
            return true;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Token refresh failed: " << e.what() << std::endl;
    }
    return false;
}

#pragma once

#include <string>
#include <curl/curl.h>

class DeribitAuth {
public:
    std::string api_key;
    std::string api_secret;
    std::string access_token;
    std::string refresh_token;
    bool is_authenticated;
    CURL* curl;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
    std::string makeRequest(const std::string& endpoint, const std::string& params);
    std::string extractToken(const std::string& json_response, const std::string& token_key);

public:
    DeribitAuth(const std::string& api_key, const std::string& api_secret);
    ~DeribitAuth();
    
    bool authenticate();
    bool isAuthenticated() const { return is_authenticated; }
    std::string getAccessToken() const { return access_token; }
    bool refreshAccessToken();
};
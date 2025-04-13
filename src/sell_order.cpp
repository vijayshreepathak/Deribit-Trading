#include "sell_order.hpp"
#include <iostream>
#include <string>
#include <curl/curl.h>

SellOrder::SellOrder(const std::string &client_id, const std::string &client_secret)
    : client_id(client_id), client_secret(client_secret) {}

SellOrder::~SellOrder() {}

std::string SellOrder::generate_signature(const std::string &data) {
    return data + "_signature"; 
}

std::string SellOrder::send_request(const std::string &url, const std::string &data) {
    CURL *curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if(response_code == 200) {
                // Handle the response, e.g., capture the response in a string
            }
        }
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
    return response;
}

bool SellOrder::place_sell_order(const std::string &instrument, const std::string &type, int quantity) {
    std::string url = "https://test.deribit.com/api/v1/private/sell";

    std::string data = "instrument=" + instrument + "&type=" + type + "&quantity=" + std::to_string(quantity);
    
    std::string signature = generate_signature(data);
    data += "&signature=" + signature;

    std::string response = send_request(url, data);
    std::cout << "Response: " << response << std::endl;

    if (response.find("error") != std::string::npos) {
        return false;  // Order failed
    }
    return true;  // Order placed successfully
}

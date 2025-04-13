#ifndef GET_ORDERBOOK_HPP
#define GET_ORDERBOOK_HPP

#include <string>

class GetOrderBook {
public:
    GetOrderBook(const std::string& api_key, const std::string& api_secret);
    bool getAccessToken();
    bool sendHttpRequest(const std::string& instrument);
    bool getOrderBook(const std::string& instrument);

private:
    std::string api_key_;
    std::string api_secret_;
    std::string access_token_;
};

#endif // GET_ORDERBOOK_HPP 
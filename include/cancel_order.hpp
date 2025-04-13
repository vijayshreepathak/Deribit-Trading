#ifndef CANCEL_ORDER_HPP
#define CANCEL_ORDER_HPP

#include <string>

class CancelOrder {
public:
    CancelOrder(const std::string& api_key, const std::string& api_secret);
    bool cancelOrder(const std::string& order_id);

private:
    std::string api_key_;
    std::string api_secret_;
    std::string access_token_;

    bool getAccessToken();
    bool sendCancelRequest(const std::string& order_id);
};

#endif // CANCEL_ORDER_HPP

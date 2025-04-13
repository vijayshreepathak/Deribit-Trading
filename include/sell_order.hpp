#ifndef SELL_ORDER_HPP
#define SELL_ORDER_HPP

#include <string>

class SellOrder {
public:
    // Constructor and Destructor
    SellOrder(const std::string &client_id, const std::string &client_secret);
    ~SellOrder();

    // Method to place a sell order
    bool place_sell_order(const std::string &instrument, const std::string &type, int quantity);

private:
    std::string client_id;
    std::string client_secret;

    // Helper methods
    std::string generate_signature(const std::string &data);
    std::string send_request(const std::string &url, const std::string &data);
};

#endif // SELL_ORDER_HPP




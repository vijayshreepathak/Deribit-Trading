#ifndef MODIFY_ORDER_HPP
#define MODIFY_ORDER_HPP

#include <string>

class ModifyOrder {
public:
    ModifyOrder(const std::string& api_key, const std::string& api_secret);

    // Function to modify an existing order with a new price and quantity
    bool modifyOrder(const std::string& order_id, double price, int quantity);

private:
    // Helper function to get the access token using API credentials
    bool getAccessToken();

    // Helper function to send the modify order request to Deribit
    bool sendModifyRequest(const std::string& order_id, double price, int quantity);

    // API credentials and access token
    std::string api_key_;
    std::string api_secret_;
    std::string access_token_;
};

#endif // MODIFY_ORDER_HPP

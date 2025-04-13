#include <iostream>
#include "modify_order.hpp"

int main() {
    // Example API Key and Secret (replace with your actual credentials)
    std::string api_key;  // Replace with your API key
    std::string api_secret;  // Replace with your API secret

    // Instantiate the ModifyOrder class
    ModifyOrder modifyOrder(api_key, api_secret);

    // Example order details (replace these with actual order ID, price, and quantity)
    std::string order_id = "order12345";  // Replace with your order ID
    double price = 50000.0;  // New price for the order
    int quantity = 1;  // New quantity for the order

    // Attempt to modify the order
    bool success = modifyOrder.modifyOrder(order_id, price, quantity);

    if (success) {
        std::cout << "Order modification successful!" << std::endl;
    } else {
        std::cerr << "Order modification failed!" << std::endl;
    }

    return 0;
}

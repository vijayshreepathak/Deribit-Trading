#include "sell_order.hpp"
#include<iostream>
int main() {
    std::string client_id ;  // Your client ID
    std::string client_secret;  // Your client secret

    // Create SellOrder object
    SellOrder sell_order(client_id, client_secret);

    // Test the sell order placement
    if (sell_order.place_sell_order("ETH-PERPETUAL", "market", 10)) {
        std::cout << "Sell order placed successfully!" << std::endl;
    } else {
        std::cout << "Failed to place sell order." << std::endl;
    }

    return 0;
}
//place_sell_order
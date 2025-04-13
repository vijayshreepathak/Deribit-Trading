#include "get_orderbook.hpp"
#include <iostream>

int main() {
    std::string api_key;  // Replace with your API key
    std::string api_secret;  // Replace with your API secret

    GetOrderBook get_orderbook(api_key, api_secret);

    // Test HTTP request to get the order book for a specific instrument
    std::cout << "Testing HTTP request to get order book:" << std::endl;
    if (get_orderbook.getOrderBook("BTC-USD")) {
        std::cout << "HTTP Request Successful!" << std::endl;
    } else {
        std::cout << "HTTP Request Failed!" << std::endl;
    }

    return 0;
}

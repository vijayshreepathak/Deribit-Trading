#include "get_orderbook.hpp"
#include <iostream>

int main() {
    // Initialize with your API credentials
    GetOrderBook orderBook("hAWsxCAq", "b0-v8sDqUcUbj31SzQeKEddNwZbh1GbudDeeNVwkL0Y");
    
    // Example: Get orderbook for BTC-PERPETUAL
    if (orderBook.getOrderBook("BTC-PERPETUAL")) {
        std::cout << "Successfully retrieved orderbook for BTC-PERPETUAL" << std::endl;
    } else {
        std::cerr << "Failed to retrieve orderbook" << std::endl;
        return 1;
    }

    return 0;
} 
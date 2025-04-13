// test_cancel_order.cpp

#include "cancel_order.hpp"
#include <iostream>

int main() {
    std::string api_key; 
    std::string api_secret;

    CancelOrder cancel_order(api_key, api_secret);

    std::string order_id = "<ETH-16069197631>";  // Replace with an actual order ID

    if (cancel_order.cancelOrder(order_id)) {
        std::cout << "Order cancellation successful" << std::endl;
    } else {
        std::cout << "Order cancellation failed" << std::endl;
    }

    return 0;
}

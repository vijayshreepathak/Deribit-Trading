
#include "include/auth.hpp"
#include "include/order.hpp"
#include "include/account.hpp"
#include <iostream>

int main() {
    const std::string API_KEY;
    const std::string API_SECRET;

    try {
        // Initialize authentication
        DeribitAuth auth(API_KEY, API_SECRET);

        std::cout << "Authenticating...\n";
        if (!auth.authenticate()) {
            std::cerr << "Authentication failed! Please check your API key and secret.\n";
            return 1;
        }
        std::cout << "Authentication successful!\n\n";

        // Create account object and get summary
        DeribitAccount account(auth);
        std::cout << "Fetching account summary...\n";
        std::string summary = account.getAccountSummary();
        std::cout << "Account Summary:\n" << summary << std::endl;

        // Create order object and place a buy order
        DeribitOrder order(auth);
        
        // Choose a valid instrument from Deribit's available instruments
        // You can get a list of available instruments using Deribit's API
        std::string instrument = "ETH-PERPETUAL";  
        int quantity = 10;  
        std::string type = "market";  // or "limit"

        // For limit order, specify a price
        double price = 0.0;  // Set to 0 for market orders
        // For limit order, set an appropriate price
        // price = 50000.0;  // Example price for a limit order

        std::cout << "Placing order for instrument: " << instrument << "\n";
        std::string order_response = order.placeBuyOrder(instrument, type, quantity, price);

        // Output the response from placing the order
        std::cout << "Order Response:\n" << order_response << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
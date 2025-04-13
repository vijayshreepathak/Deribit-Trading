
// test_account.cpp (Test file)
#include "include/auth.hpp"
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
        std::cout << "API Key: " << API_KEY << "\n";
        std::cout << "API Secret: " << API_SECRET << "\n";

        // Create account object and get summary
        DeribitAccount account(auth);
        std::cout << "Fetching account summary...\n";

        std::string summary = account.getAccountSummary();
        std::cout << "Account Summary:\n" << summary << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
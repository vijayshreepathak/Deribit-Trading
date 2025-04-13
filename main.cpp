#include "include/auth.hpp"
#include "include/order.hpp"
#include "include/account.hpp"
#include "get_orderbook.hpp"
#include "sell_order.hpp"
#include "cancel_order.hpp"
#include "include/account.hpp"
#include "include/modify_order.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <cmath>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <limits>
#include <exception>
#include <stdexcept>
#include <functional>
#include <type_traits>
#include <initializer_list>
#include <iterator>
#include <array>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <queue>
#include <stack>
#include <deque>
#include <forward_list>
#include <tuple>
#include <regex>    
using namespace std;
int main() {
    try {
        std::string api_key;
        std::string api_secret;
        cout<<"Enter API key: ";
        cin>>api_key;
        cout<<"Enter API secret";
        cin>>api_secret;
        DeribitAuth auth(api_key, api_secret);
        
        if (auth.authenticate()) {
            std::cout << "Authentication successful!" << std::endl;
            std::cout << "Access token: " << auth.getAccessToken() << std::endl;


            cout<<"Choose an option: "<<endl;
            cout<<"1. Place a buy order"<<endl;
            cout<<"2. Place a sell order"<<endl;
            cout<<"3. Modify an order"<<endl;
            cout<<"4. Cancel an order"<<endl;
            cout<<"5. Get account summary"<<endl;
            cout<<"6. Get order book"<<endl;

            int choice; cin>> choice;

            
            if(choice == 1){
                    DeribitOrder order(auth);
                
                    std::string instrument; // = "ETH-PERPETUAL"; 
                    cout<<"Enter instrument: ";
                    cin>>instrument; 
                    int quantity; // = 10;  
                    cout<<"Enter quantity: ";
                    cin>>quantity;
                    std::string type; // = "market";  // or "limit"
                    cout<<"Enter order type: ";
                    cin>>type;
                    // For limit order, specify a price
                    double price = 0.0;  // Set to 0 for market orders
                    if(type == "limit"){
                        cout<<"Enter price: ";
                        cin>>price;
                    }
                    // For limit order, set an appropriate price
         

                    std::cout << "Placing order for instrument: " << instrument << "\n";
                    std::string order_response = order.placeBuyOrder(instrument, type, quantity, price);

                    // Output the response from placing the order
                    std::cout << "Order Response:\n" << order_response << std::endl;
            }

            else if(choice==2){
                SellOrder sell_order(api_key, api_secret);

                // Test the sell order placement
                if (sell_order.place_sell_order("ETH-PERPETUAL", "market", 10)) {
                    std::cout << "Sell order placed successfully!" << std::endl;
                } else {
                    std::cout << "Failed to place sell order." << std::endl;
                }

            }

            else if(choice == 3){
                ModifyOrder modifyOrder(api_key, api_secret);
                cout<<"Enter order id: ";
                std::string order_id;
                cin>>order_id;
                cout<<"Enter new price: ";
                double price;
                cin>>price;
                cout<<"Enter new quantity: ";
                int quantity;
                cin>>quantity;
                 bool success = modifyOrder.modifyOrder(order_id, price, quantity);

                if (success) {
                    std::cout << "Order modification successful!" << std::endl;
                } else {
                    std::cerr << "Order modification failed!" << std::endl;
                }
            }

            else if(choice == 4){

                CancelOrder cancel_order(api_key, api_secret);

                std::string order_id;// = "<ETH-16069197631>";  // Replace with an actual order ID
                cout<<"Enter order id: ";
                cin>>order_id;
                if (cancel_order.cancelOrder(order_id)) {
                    std::cout << "Order cancellation successful" << std::endl;
                } else {
                    std::cout << "Order cancellation failed" << std::endl;
                }

            }

            else if(choice == 5){

                DeribitAccount account(auth);
                std::cout << "Fetching account summary...\n";

                std::string summary = account.getAccountSummary();
                std::cout << "Account Summary:\n" << summary << std::endl;

            }

            else if(choice== 6){

                GetOrderBook get_orderbook(api_key, api_secret);

                // Test HTTP request to get the order book for a specific instrument
                std::cout << "Testing HTTP request to get order book:" << std::endl;
                if (get_orderbook.getOrderBook("BTC-USD")) {
                    std::cout << "HTTP Request Successful!" << std::endl;
                } else {
                    std::cout << "HTTP Request Failed!" << std::endl;
                }
            }
            
        } else {
            std::cout << "Authentication failed!" << std::endl;
            cout<<"Try again with correct credentials"<<endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
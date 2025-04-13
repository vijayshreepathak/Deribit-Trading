#pragma once
#include "auth.hpp"
#include <string>

class DeribitOrder {
private:
    DeribitAuth& auth;
    std::string makeAuthenticatedPostRequest(const std::string& endpoint, const std::string& payload);

public:
    explicit DeribitOrder(DeribitAuth& auth_instance);
    std::string placeBuyOrder(const std::string& instrument, const std::string& type, int quantity, double price = 0.0);
};
#pragma once
#include "auth.hpp"
#include <string>

class DeribitAccount {
private:
    DeribitAuth& auth;
    std::string makeAuthenticatedRequest(const std::string& endpoint);

public:
    explicit DeribitAccount(DeribitAuth& auth_instance);
    std::string getAccountSummary();
};
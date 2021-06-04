#pragma once
#include <string>
#include <vector>

class customResponse {
   public:
    customResponse() = default;
    virtual ~customResponse() = default;
    virtual void processResult(const std::vector<bool>& res, const unsigned int& K, const std::string& current_header, const std::string& current_read) = 0;
};
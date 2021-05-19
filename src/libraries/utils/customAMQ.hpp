#pragma once
#include <string>

/// The abstract AMQ interface.
class customAMQ {
   public:
    customAMQ() = default;
    virtual ~customAMQ() = default;

    virtual bool contains(const std::string& x) const {
        std::cerr << "Should never be called." << std::endl;
        exit(1);
        return false;
    };
};
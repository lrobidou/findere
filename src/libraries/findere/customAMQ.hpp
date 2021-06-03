#pragma once
#include <iostream>
#include <string>

/**
 * @brief A vritual wrapper class to wrap your custom AMQ.
 * @author Lucas Robidou
 * @since Thu Jun 03 2021
 */
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
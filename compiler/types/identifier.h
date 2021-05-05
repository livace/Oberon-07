#pragma once

#include <iostream>

class Identifier {
public:
    Identifier(std::string identifier) : identifier_(std::move(identifier)) {
        std::cout << "IDENTIFIER " << identifier_ << std::endl;
    }
private:
    std::string identifier_;
};

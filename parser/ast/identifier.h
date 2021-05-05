#pragma once

#include "ast.h"

#include <iostream>

class Identifier : public Ast {
public:
    Identifier(std::string identifier) : identifier_(std::move(identifier)) {}

    std::string identifier() {
        return identifier_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
    
private:
    std::string identifier_;
};

#pragma once

#include <iostream>

#include "ast.h"

class Type : public Ast {
public:
    Type(std::string name) : name_(name) {}

    std::string name() {
        return name_;
    }
    
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    std::string name_;
};

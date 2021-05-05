#pragma once

#include "ast.h"

class String : public Ast {
public:
    String(std::string value) : value_(std::move(value)) {}

    std::string value() {
        return value_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    std::string value_;
};

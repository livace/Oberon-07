#pragma once

#include <variant>
#include "ast.h"

class Number : public Ast {
public:
    Number(int value) : value_(value) {}
    Number(float value) : value_(value) {}

    std::variant<int, float> value() {
        return value_;
    }

    int int_value() {
        return std::visit([] (const auto& value) -> int {return value;}, value_);
    }

    float float_value() {
        return std::visit([] (const auto& value) -> float {return value;}, value_);
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    std::variant<int, float> value_;
};

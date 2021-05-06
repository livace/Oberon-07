#pragma once

#include "ast.h"

class Real : public Ast {
public:
    Real(int value) : value_(value) {}

    int value() {
        return value_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    int value_;
};

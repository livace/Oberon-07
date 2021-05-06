#pragma once

#include "unary_operator.h"

class UnaryPlus : public UnaryOperator {
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

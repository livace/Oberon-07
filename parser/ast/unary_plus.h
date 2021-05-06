#pragma once

#include "unary_operator.h"

class UnaryMinus : public UnaryOperator {
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

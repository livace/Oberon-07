#pragma once

#include "mul_operator.h"

class Multiplication : public MulOperator {
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

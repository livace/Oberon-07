#pragma once

#include "mul_operator.h"

class Modulo : public MulOperator {
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

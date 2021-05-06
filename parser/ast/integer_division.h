#pragma once

#include "mul_operator.h"

class IntegerDivision : public MulOperator {
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

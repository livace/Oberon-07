#pragma once

#include "mul_operator.h"

class Division : public MulOperator {
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

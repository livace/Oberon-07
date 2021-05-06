#pragma once

#include "mul_operator.h"

class LogicalConjunction : public MulOperator {
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

#pragma once

#include "add_operator.h"

class LogicalDisjunction : public AddOperator {
    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    
};

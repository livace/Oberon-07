#pragma once

#include "add_operator.h"

class BinaryMinus : public AddOperator {
    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    
};

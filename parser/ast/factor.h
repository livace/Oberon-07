#pragma once

#include "add_operator.h"

class BinaryPlus : public AddOperator {
    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    
}

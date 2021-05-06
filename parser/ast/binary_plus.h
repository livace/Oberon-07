#pragma once

#include "ast.h"

class BinaryPlus : public AddOperator {
    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    
};

#pragma once

#include "ast.h"

class NilFactor : public Factor {
public:
    NilFactor() {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    
};

#pragma once

#include "ast.h"

class TrueFactor : public Factor {
public:
    TrueFactor() {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    
};

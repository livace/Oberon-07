#pragma once

#include "ast.h"

class FalseFactor : public Factor {
public:
    FalseFactor() {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    
};

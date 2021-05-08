#pragma once

#include "ast.h"
#include "factor.h"

class NegationFactor : public Factor {
public:
    NegationFactor(Factor *factor) : factor_(factor) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Factor* factor() {
        return factor_;
    }

private:
    Factor* factor_;
};

#pragma once

#include "ast.h"
#include "number.h"

class NumberFactor : public Factor {
public:
    NumberFactor(Number *number) : number_(number) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Number* number() {
        return number_;
    }

private:
    Number* number_;
};

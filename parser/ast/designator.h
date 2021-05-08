#pragma once

#include "ast.h"
#include "qualident.h"
#include "selectors.h"

class Designator : public Ast {
public:
    Designator(Qualident *qualident, Selectors *selectors = nullptr) : selector_(qualident), selectors_(selectors) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Qualident *qualident() {
        return selector_;
    }

    Selectors *selectors() {
        return selectors_;
    }

private:
    Qualident *selector_;
    Selectors *selectors_;
};

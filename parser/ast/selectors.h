#pragma once

#include "ast.h"
#include "selector.h"

class Selectors : public Ast {
public:
    Selectors(Selector *selector, Selectors *selectors = nullptr) : selector_(selector), selectors_(selectors) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Selector *selector() {
        return selector_;
    }

    Selectors *selectors() {
        return selectors_;
    }

private:
    Selector *selector_;
    Selectors *selectors_;
};

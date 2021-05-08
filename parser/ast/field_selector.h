#pragma once

#include "selector.h"
#include "identifier.h"

class FieldSelector : public Selector {
public:
    FieldSelector(Identifier *ident) : ident_(ident) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Identifier *ident() {
        return ident_;
    }

private:
    Identifier *ident_;
};

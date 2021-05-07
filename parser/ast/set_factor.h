#pragma once

#include "ast.h"
#include "set.h"

class SetFactor : public Factor {
public:
    SetFactor(Set *set) : set_(set) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Set* set() {
        return set_;
    }

private:
    Set* set_;
};

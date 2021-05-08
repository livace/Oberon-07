#pragma once

#include "selector.h"
#include "exp_list.h"

class ArraySelector : public Selector {
public:
    ArraySelector(ExpList *exp_list) : exp_list_(exp_list) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    ExpList *exp_list() {
        return exp_list_;
    }

private:
    ExpList *exp_list_;
};

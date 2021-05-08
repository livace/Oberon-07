#pragma once

#include "ast.h"

#include <iostream>

#include "exp_list.h"

class ActualParameters : public Ast {
public: 
    ActualParameters(ExpList *exp_list = nullptr) : exp_list_(exp_list) {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

    ExpList* expList() {
        return exp_list_;
    }

private:
    ExpList* exp_list_;
};

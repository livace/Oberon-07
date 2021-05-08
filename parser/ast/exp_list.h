#pragma once

#include "ast.h"
#include "expression.h"

class ExpList : public Ast {
public:
    ExpList(Expression *expression, ExpList *exp_list = nullptr) : expression_(expression), exp_list_(exp_list) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Expression *expression() {
        return expression_;
    }

    ExpList *expList() {
        return exp_list_;
    }

private:
    Expression *expression_;
    ExpList *exp_list_;
};

#pragma once

#include "expression.h"
#include "ast.h"

class ConstExpression : public Ast {
public:
    ConstExpression(Expression *expression) : expression_(expression) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Expression *expression() {
        return expression_;
    }

private:
    Expression *expression_;
};

#pragma once

#include "ast.h"
#include "expression.h"

class ExpressionFactor : public Factor {
public:
    ExpressionFactor(Expression *expression) : expression_(expression) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Expression* expression() {
        return expression_;
    }

private:
    Expression* expression_;
};

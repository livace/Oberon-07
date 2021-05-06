#pragma once

#include "const_expression.h"
#include "ast.h"

class Length : public Ast {
public:
    Length(ConstExpression *expression) : expression_(expression) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    ConstExpression *constExpression() {
        return expression_;
    }

private:
    ConstExpression *expression_;
};

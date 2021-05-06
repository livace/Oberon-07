#pragma once

#include "ast.h"

#include "unary_operator.h"
#include "terms.h"

class SimpleExpression : public Ast {
public:
    SimpleExpression(Terms* terms, UnaryOperator* unary_operator = nullptr) : terms_(terms), unary_operator_(unary_operator) {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

    Terms* terms() {
        return terms_;
    }

    UnaryOperator* unaryOperator() {
        return unary_operator_;
    }

private:
    Terms* terms_;
    UnaryOperator* unary_operator_;
};

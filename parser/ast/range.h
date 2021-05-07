#pragma once

#include "ast.h"
#include "expression.h"

class Range : public Element {
public:
    Range(Expression *from, Expression *to) : from_(from), to_(to) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Expression *from() {
        return from_;
    }

    Expression *to() {
        return to_;
    }

private:
    Expression *from_;
    Expression *to_;
};

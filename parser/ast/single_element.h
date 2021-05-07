#pragma once

#include "ast.h"
#include "expression.h"

class SingleElement : public Element {
public:
    SingleElement(Expression *expression) : expression_(expression) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Expression *expression() {
        return expression_;
    }

private:
    Expression *expression_;
};

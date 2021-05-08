#pragma once

#include "ast.h"

#include "simple_expression.h"
#include "relation.h"

class Expression : public Ast {
public:
    Expression(SimpleExpression *primary, Relation *relation, SimpleExpression *secondary)
        : primary_(primary)
        , relation_(relation)
        , secondary_(secondary) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    SimpleExpression *primary() {
        return primary_;
    }

    Relation *relation() {
        return relation_;
    }

    SimpleExpression *secondary() {
        return secondary_;
    }

private:
    SimpleExpression *primary_;
    Relation *relation_;
    SimpleExpression *secondary_;
};

#pragma once

#include "identdef.h"
#include "ast.h"

class ConstDeclaration : public Ast {
public:
    ConstDeclaration(IdentDef *identifier, ConstExpression *const_expression)
        : identifier_(identifier)
        , const_expression_(const_expression) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    IdentDef *identifier() {
        return identifier_;
    }

    ConstExpression *constExpression() {
        return const_expression_;
    }

private:
    IdentDef *identifier_;
    ConstExpression *const_expression_;
};

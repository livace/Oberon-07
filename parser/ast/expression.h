#pragma once

#include "ast.h"

class Expression : public Ast {
public:
    Expression() {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }
};

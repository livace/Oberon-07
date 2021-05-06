#pragma once

#include "ast.h"

class Term : public Ast {
public:
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

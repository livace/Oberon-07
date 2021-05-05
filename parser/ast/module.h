#pragma once

#include "ast.h"

class Module : public Ast {
public:
    Module() {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

#pragma once

#include <iostream>

#include "ast.h"

class Type : public Ast {
public:
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

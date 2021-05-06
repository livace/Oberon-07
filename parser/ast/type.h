#pragma once

#include <iostream>

#include "ast.h"

class Type : virtual public Ast {
public:
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

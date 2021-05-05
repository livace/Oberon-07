#pragma once

#include "ast.h"

class ProcedureHeading : public Ast {
public:
    ProcedureHeading() {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

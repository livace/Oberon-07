#pragma once

#include "ast.h"

class ProcedureHeading : public Ast {
public:
    ProcedureHeading() {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }
};

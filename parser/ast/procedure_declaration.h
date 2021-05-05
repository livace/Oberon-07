#pragma once

#include "ast.h"

#include <iostream>

class ProcedureDeclaration : public Ast {
public: 
    ProcedureDeclaration(ProcedureHeading *heading) : heading_(heading) {
        std::cerr << "Create ProcedureDeclaration Ast\n";
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    ProcedureHeading* procedureHeading() {
        return heading_;
    }

private:
    ProcedureHeading* heading_;
};

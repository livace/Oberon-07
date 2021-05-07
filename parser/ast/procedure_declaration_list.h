#pragma once

#include "procedure_declaration.h"
#include "ast.h"

#include <vector>

class ProcedureDeclarationList : public Ast {
public:
    ProcedureDeclarationList(ProcedureDeclaration *procedure_declaration) {
        procedure_declarations_.push_back(procedure_declaration);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addProcedureDeclaration(ProcedureDeclaration *procedure_declaration) {
        procedure_declarations_.push_back(procedure_declaration);
    }

    const std::vector<ProcedureDeclaration*>& procedureDeclarations() const {
        return procedure_declarations_;
    }

private:
    std::vector<ProcedureDeclaration*> procedure_declarations_;
};

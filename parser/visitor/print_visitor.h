#include "visitor.h"

#include <iostream>

#include "parser/ast/procedure_declaration.h"

class PrintVisitor : public Visitor {
    void visit(ProcedureDeclaration *procedure_declaration) {
        std::cerr << "visit ProcedureDeclaration\n";
        procedure_declaration->procedureHeading()->accept(*this);
    }

    void visit(ProcedureHeading *procedure_heading) {
        std::cerr << "visit ProcedureHeading\n";
    }  
};

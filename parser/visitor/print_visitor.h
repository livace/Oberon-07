#include "visitor.h"

#include <iostream>

#include "parser/ast/procedure_declaration.h"

class PrintVisitor {
    void visit(ProcedureDeclaration *procedure_declaration) {
        std::cerr << "visit ProcedureDeclaration\n";
    }
}

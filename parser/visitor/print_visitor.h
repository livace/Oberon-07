#include "visitor.h"

#include <iostream>

#include "parser/ast/identifier.h"
#include "parser/ast/procedure_heading.h"
#include "parser/ast/procedure_declaration.h"
#include "parser/ast/type.h"
#include "parser/ast/variable_declaration.h"


class PrintVisitor : public Visitor {
    void visit(Identifier *indentifier) {
        std::cerr << indentifier->identifier();
    }  

    void visit(ProcedureDeclaration *procedure_declaration) {
        std::cerr << "PROCEDURE ";
        procedure_declaration->procedureHeading()->accept(*this);
    }

    void visit(ProcedureHeading *procedure_heading) {
        std::cerr << "<some name>";
    }  

    void visit(Type *type) {
        std::cerr << type->name();
    }  

    void visit(VariableDeclaration *variable_declaration) {
        variable_declaration->identifier()->accept(*this);
        std::cerr << ":";
        variable_declaration->type()->accept(*this);
    }  
    
};

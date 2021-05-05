#include "visitor.h"

#include <iostream>

#include <parser/ast/identifier.h>
#include <parser/ast/procedure_declaration.h>
#include <parser/ast/procedure_heading.h>
#include <parser/ast/type.h>
#include <parser/ast/variable_declaration.h>
#include <parser/ast/qualident.h>
#include <parser/ast/module.h>
#include <parser/ast/const_declaration.h>
#include <parser/ast/const_expression.h>
#include <parser/ast/expression.h>
#include <parser/ast/identdef.h>
#include <parser/ast/number.h>
#include <parser/ast/string.h>
#include <parser/ast/root.h>

class PrintVisitor : public Visitor {
    void visit(Identifier *identifier) {
        std::cerr << identifier->identifier();
    }  

    void visit(ProcedureDeclaration *procedure_declaration) {
        std::cerr << "PROCEDURE";
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

    void visit(Qualident *qualident) {
        if (auto prefix = qualident->prefix(); prefix) {
            prefix->accept(*this);
        }
        qualident->identifier()->accept(*this);
    }

    void visit(Module *module) {
    }

    void visit(ConstDeclaration *const_declaration) {
        const_declaration->identifier()->accept(*this);
        const_declaration->constExpression()->accept(*this);
    }

    void visit(ConstExpression *const_expression) {
        const_expression->expression()->accept(*this);
    }

    void visit(Expression *expression) {
    }

    void visit(IdentDef *identdef) {
        std::cerr << identdef->identifier() << ", is_exported: " << identdef->isExported();
    }

    void visit(Number *number) {
        std::cerr << number->float_value();
    }

    void visit(String *string) {
        std::cerr << string->value();
    }

    void visit(Root *root) {
        root->module()->accept(*this);
    }

    
};

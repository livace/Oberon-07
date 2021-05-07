#pragma once

#include "const_declaration_list.h"
#include "type_declaration_list.h"
#include "variable_declaration_list.h"
#include "procedure_declaration_list.h"

#include "ast.h"

class DeclarationSequence : public Type {
public:
    DeclarationSequence(ConstDeclarationList *const_declaration_list,
                        TypeDeclarationList *type_declaration_list,
                        VariableDeclarationList *variable_declaration_list,
                        ProcedureDeclarationList *procedure_declaration_list)
            : const_declaration_list_(const_declaration_list)
            , type_declaration_list_(type_declaration_list)
            , variable_declaration_list_(variable_declaration_list)
            , procedure_declaration_list_(procedure_declaration_list) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    ConstDeclarationList *constDeclarationList() {
        return const_declaration_list_;
    }

    TypeDeclarationList *typeDeclarationList() {
        return type_declaration_list_;
    }

    VariableDeclarationList *variableDeclarationList() {
        return variable_declaration_list_;
    }

    ProcedureDeclarationList *procedureDeclarationList() {
        return procedure_declaration_list_;
    }

private:
    ConstDeclarationList *const_declaration_list_;
    TypeDeclarationList *type_declaration_list_;
    VariableDeclarationList *variable_declaration_list_;
    ProcedureDeclarationList *procedure_declaration_list_;
};

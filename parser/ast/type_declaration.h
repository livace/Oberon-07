#pragma once

#include "ast.h"
#include "identdef.h"
#include "type.h"

#include <vector>

class TypeDeclaration : public Ast {
public:
    TypeDeclaration(IdentDef *ident_def, Type *type) : ident_def_(ident_def), type_(type) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    IdentDef *identDef() const {
        return ident_def_;
    }

    Type *type() {
        return type_;
    }

private:
    IdentDef *ident_def_;
    Type *type_;
};

#pragma once

#include "ast.h"
#include "identdef.h"
#include "type.h"

#include <vector>

class TypeDeclaration : public Ast {
public:
    TypeDeclaration(IdentDef *ident_def, Type *type) : ident_def_(ident_def), type_(type), original_type_(type) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    IdentDef *identDef() const {
        return ident_def_;
    }

    Type *type() {
        return type_;
    }

    Type *originalType() {
        return original_type_;
    }

    void setType(Type *type) {
        type_ = type;
    }

private:
    IdentDef *ident_def_;
    Type *type_;
    Type *original_type_;
};

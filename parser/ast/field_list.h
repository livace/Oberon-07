#pragma once

#include "ast.h"
#include "identdef_list.h"
#include "type.h"

#include <vector>

class FieldList : public Ast {
public:
    FieldList(IdentDefList *identdef_list, Type *type) : ident_list_(identdef_list), type_(type) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    IdentDefList *identList() const {
        return ident_list_;
    }

    Type *type() {
        return type_;
    }

private:
    IdentDefList *ident_list_;
    Type *type_;
};

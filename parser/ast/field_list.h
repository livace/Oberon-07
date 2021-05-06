#pragma once

#include "ast.h"
#include "ident_list.h"
#include "type.h"

#include <vector>

class FieldList : public Ast {
public:
    FieldList(IdentList *ident_list, Type *type) : ident_list_{ident_list}, type_(type) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    IdentList *identList() const {
        return ident_list_;
    }

    Type *type() {
        return type_;
    }

private:
    IdentList *ident_list_;
    Type *type_;
};

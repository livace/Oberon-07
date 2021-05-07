#pragma once

#include "length_list.h"
#include "type.h"
#include "ast.h"

class ArrayType : public Type {
public:
    ArrayType(LengthList *lengths, Type *type) : lengths_(lengths), type_(type) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    LengthList *lengths() {
        return lengths_;
    }

    Type *type() {
        return type_;
    }

private:
    LengthList *lengths_;
    Type *type_;
};

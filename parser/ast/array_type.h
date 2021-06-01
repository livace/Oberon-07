#pragma once

#include "length_list.h"
#include "type.h"
#include "ast.h"

class ArrayType : public Type {
public:
    ArrayType(LengthList *lengths, Type *type) : lengths_(lengths), type_(type), original_type_(type) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    LengthList *lengths() {
        return lengths_;
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
    LengthList *lengths_;
    Type *type_;
    Type *original_type_;
};

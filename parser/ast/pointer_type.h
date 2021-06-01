#pragma once

#include "type.h"
#include "ast.h"

class PointerType : public Type {
public:
    PointerType(Type *type) : type_(type), original_type_(type) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
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
    Type *type_;
    Type *original_type_;
};

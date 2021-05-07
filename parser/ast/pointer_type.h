#pragma once

#include "type.h"
#include "ast.h"

class PointerType : public Type {
public:
    PointerType(Type *type) : type_(type) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Type *type() {
        return type_;
    }

private:
    Type *type_;
};

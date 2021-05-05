#pragma once

#include "identifier.h"
#include "type.h"

#include "ast.h"

class VariableDeclaration : public Ast {
public:
    VariableDeclaration(Identifier *identifier, Type *type) : identifier_(identifier), type_(type) {}

    Identifier *identifier() {
        return identifier_;
    }

    Type *type() {
        return type_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    Identifier *identifier_;
    Type *type_;
};

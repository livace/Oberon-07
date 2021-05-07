#pragma once

#include "ast.h"
#include "identifier_list.h"
#include "formal_type.h"

class FPSection : public Ast {
public:
    FPSection(bool is_variable, IdentifierList *identifier_list, FormalType *formal_type)
            : is_variable_(is_variable)
            , identifier_list_(identifier_list)
            , formal_type_(formal_type) {}

    bool isVariable() {
        return is_variable_;
    }

    IdentifierList *identifierList() {
        return identifier_list_;
    }

    FormalType *formalType() {
        return formal_type_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    bool is_variable_;
    IdentifierList *identifier_list_;
    FormalType *formal_type_;
};

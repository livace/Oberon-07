#pragma once

#include "ast.h"
#include "identifier.h"

class IdentDef : public Ast {
public:
    IdentDef(Identifier *identifier, bool is_exported = false)
        : identifier_(identifier)
        , is_exported_(is_exported) {}

    std::string identifier() {
        return identifier_->identifier();
    }

    bool isExported() {
        return is_exported_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    Identifier *identifier_;
    bool is_exported_;
};

#pragma once

#include "identifier.h"
#include "ast.h"

#include <vector>

class IdentifierList : public Ast {
public:
    IdentifierList(Identifier *identifier) {
        identifiers_.push_back(identifier);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addIdentifier(Identifier *identifier) {
        identifiers_.push_back(identifier);
    }

    const std::vector<Identifier*>& identifiers() const {
        return identifiers_;
    }

private:
    std::vector<Identifier*> identifiers_;
};

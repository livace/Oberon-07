#pragma once

#include "identifier.h"
#include "ast.h"

class Import : public Ast {
public:
    Import(Identifier *identifier) : identifier_(identifier), alias_(identifier) {}
    Import(Identifier *identifier, Identifier *alias) : identifier_(identifier), alias_(alias) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Identifier *identifier() {
        return identifier_;
    }

    Identifier *alias() {
        return alias_;
    }

private:
    Identifier *identifier_;
    Identifier *alias_;
};

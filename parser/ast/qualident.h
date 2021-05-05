#pragma once

#include "identifier.h"
#include "ast.h"

class Qualident : public Ast {
public:
    Qualident(Identifier *identifier) : identifier_(identifier) {}
    Qualident(Identifier *prefix, Identifier *identifier) : prefix_(prefix), identifier_(identifier) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Identifier *prefix() {
        return prefix_;
    }

    Identifier *identifier() {
        return identifier_;
    }

private:
    Identifier *prefix_ = nullptr;
    Identifier *identifier_;
};

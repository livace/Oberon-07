#pragma once

#include "identdef.h"
#include "ast.h"

#include <vector>

class IdentDefList : public Ast {
public:
    IdentDefList(IdentDef *identdef) {
        identdefs_.push_back(identdef);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addIdentDef(IdentDef *identdef) {
        identdefs_.push_back(identdef);
    }

    const std::vector<IdentDef*>& identdefs() const {
        return identdefs_;
    }

private:
    std::vector<IdentDef*> identdefs_;
};

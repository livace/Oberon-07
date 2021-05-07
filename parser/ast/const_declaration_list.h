#pragma once

#include "const_declaration.h"
#include "ast.h"

#include <vector>

class ConstDeclarationList : public Ast {
public:
    ConstDeclarationList(ConstDeclaration *const_declaration) {
        const_declarations_.push_back(const_declaration);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addConstDeclaration(ConstDeclaration *const_declaration) {
        const_declarations_.push_back(const_declaration);
    }

    const std::vector<ConstDeclaration*>& constDeclarations() const {
        return const_declarations_;
    }

private:
    std::vector<ConstDeclaration*> const_declarations_;
};

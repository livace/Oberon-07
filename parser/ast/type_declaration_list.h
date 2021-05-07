#pragma once

#include "type_declaration.h"
#include "ast.h"

#include <vector>

class TypeDeclarationList : public Ast {
public:
    TypeDeclarationList(TypeDeclaration *type_declaration) {
        type_declarations_.push_back(type_declaration);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addTypeDeclaration(TypeDeclaration *type_declaration) {
        type_declarations_.push_back(type_declaration);
    }

    const std::vector<TypeDeclaration*>& typeDeclarations() const {
        return type_declarations_;
    }

private:
    std::vector<TypeDeclaration*> type_declarations_;
};

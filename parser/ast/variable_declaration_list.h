#pragma once

#include "variable_declaration.h"
#include "ast.h"

#include <vector>

class VariableDeclarationList : public Ast {
public:
    VariableDeclarationList(VariableDeclaration *variable_declaration) {
        variable_declarations_.push_back(variable_declaration);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addVariableDeclaration(VariableDeclaration *variable_declaration) {
        variable_declarations_.push_back(variable_declaration);
    }

    const std::vector<VariableDeclaration*>& variableDeclarations() const {
        return variable_declarations_;
    }

private:
    std::vector<VariableDeclaration*> variable_declarations_;
};

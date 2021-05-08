#pragma once

#include "statement.h"
#include "ast.h"

#include <vector>

class StatementSequence : public Ast {
public:
    StatementSequence(Statement *statement) {
        statements_.push_back(statement);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addStatement(Statement *statement) {
        statements_.push_back(statement);
    }

    const std::vector<Statement*>& statements() const {
        return statements_;
    }

private:
    std::vector<Statement*> statements_;
};

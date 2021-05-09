#pragma once

#include "statement.h"
#include "expression.h"
#include "statement_sequence.h"
#include "ast.h"

class RepeatStatement : public Statement {
public:
    RepeatStatement(StatementSequence *body, Expression *expression)
            : body_(body)
            , expression_(expression) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    StatementSequence *body() {
        return body_;
    }

    Expression *expression() {
        return expression_;
    }

private:
    StatementSequence *body_;
    Expression *expression_;
};

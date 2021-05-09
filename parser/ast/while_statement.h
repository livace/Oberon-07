#pragma once

#include "expression.h"
#include "elsif_while_list.h"
#include "statement_sequence.h"
#include "statement.h"
#include "ast.h"

class WhileStatement : public Statement {
public:
    WhileStatement(Expression *expression, StatementSequence *body, ElsifWhileList *else_list)
            : expression_(expression)
            , body_(body)
            , else_list_(else_list) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Expression *expression() {
        return expression_;
    }

    StatementSequence *body() {
        return body_;
    }

    ElsifWhileList *elseList() {
        return else_list_;
    }

private:
    Expression *expression_;
    StatementSequence *body_;
    ElsifWhileList *else_list_;
};

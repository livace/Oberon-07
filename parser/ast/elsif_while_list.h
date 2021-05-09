#pragma once

#include "expression.h"
#include "statement_sequence.h"
#include "ast.h"

#include <vector>

class ElsifWhileList : public Ast {
public:
    ElsifWhileList(Expression *expression, StatementSequence *statement_sequence, ElsifWhileList *elsif_while_list)
            : expression_(expression)
            , statement_sequence_(statement_sequence)
            , elsif_while_list_(elsif_while_list) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Expression *expression() {
        return expression_;
    }

    StatementSequence *statementSequence() {
        return statement_sequence_;
    }

    ElsifWhileList *elsifWhileList() {
        return elsif_while_list_;
    }

private:
    Expression *expression_;
    StatementSequence *statement_sequence_;
    ElsifWhileList *elsif_while_list_;
};

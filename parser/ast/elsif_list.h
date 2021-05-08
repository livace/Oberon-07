#pragma once

#include "expression.h"
#include "statement_sequence.h"
#include "ast.h"

#include <vector>

class ElsifList : public Ast {
public:
    ElsifList(Expression *expression, StatementSequence *statement_sequence, ElsifList *elsif_list)
        : expression_(expression)
        , statement_sequence_(statement_sequence)
        , elsif_list_(elsif_list) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Expression *expression() {
        return expression_;
    }

    StatementSequence *statementSequence() {
        return statement_sequence_;
    }

    ElsifList *elsifList() {
        return elsif_list_;
    }

private:
    Expression *expression_;
    StatementSequence *statement_sequence_;
    ElsifList *elsif_list_;
};

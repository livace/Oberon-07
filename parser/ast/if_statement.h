#pragma once

#include "expression.h"
#include "statement_sequence.h"
#include "elsif_list.h"
#include "statement.h"
#include "ast.h"

class IfStatement : public Statement {
public:
    IfStatement(Expression *expression, StatementSequence *then_statements,
            ElsifList *elsif_list, StatementSequence *else_statements)
        : expression_(expression)
        , then_statements_(then_statements)
        , elsif_list_(elsif_list)
        , else_statements_(else_statements) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Expression *expression() {
        return expression_;
    }

    StatementSequence *thenStatements() {
        return then_statements_;
    }

    ElsifList *elsifList() {
        return elsif_list_;
    }

    StatementSequence *elseStatements() {
        return else_statements_;
    }

private:
    Expression *expression_{nullptr};
    StatementSequence *then_statements_{nullptr};
    ElsifList *elsif_list_{nullptr};
    StatementSequence *else_statements_{nullptr};
};

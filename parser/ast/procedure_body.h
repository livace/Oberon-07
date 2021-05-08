#pragma once

#include "declaration_sequence.h"
#include "statement_sequence.h"
#include "expression.h"

#include "ast.h"

class ProcedureBody : public Ast {
public:
    ProcedureBody(DeclarationSequence *declaration_sequence, StatementSequence *body,
            Expression *return_expression)
        : declaration_sequence_(declaration_sequence)
        , body_(body)
        , return_expression_(return_expression) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    DeclarationSequence *declarationSequence() {
        return declaration_sequence_;
    }

    StatementSequence *body() {
        return body_;
    }

    Expression *returnExpression() {
        return return_expression_;
    }

private:
    DeclarationSequence *declaration_sequence_;
    StatementSequence *body_;
    Expression *return_expression_;
};

#pragma once

#include "identifier.h"
#include "expression.h"
#include "const_expression.h"
#include "statement_sequence.h"
#include "statement.h"
#include "ast.h"

class ForStatement : public Statement {
public:
    ForStatement(Identifier *variable_name, Expression *variable_expression, Expression *to_expression
            , ConstExpression *by_expression, StatementSequence *body)
        : variable_name_(variable_name)
        , variable_expression_(variable_expression)
        , to_expression_(to_expression)
        , by_expression_(by_expression)
        , body_(body) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Identifier *variableName() {
        return variable_name_;
    }

    Expression *variableExpression() {
        return variable_expression_;
    }

    Expression *toExpression() {
        return to_expression_;
    }

    ConstExpression *byExpression() {
        return by_expression_;
    }

    StatementSequence *body() {
        return body_;
    }

private:
    Identifier *variable_name_;
    Expression *variable_expression_;
    Expression *to_expression_;
    ConstExpression *by_expression_;
    StatementSequence *body_;
};

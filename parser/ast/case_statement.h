#pragma once

#include "expression.h"
#include "case_list.h"
#include "statement.h"
#include "ast.h"

class CaseStatement : public Statement {
public:
    CaseStatement(Expression *expression, CaseList *cases)
        : expression_(expression)
        , cases_(cases) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Expression *expression() {
        return expression_;
    }

    CaseList *cases() {
        return cases_;
    }

private:
    Expression *expression_;
    CaseList *cases_;
};

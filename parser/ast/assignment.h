#pragma once

#include "designator.h"
#include "expression.h"
#include "statement.h"

#include "ast.h"

class Assignment : public Statement {
public:
    Assignment(Designator *designator, Expression *expression)
            : designator_(designator)
            , expression_(expression) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Designator *designator() {
        return designator_;
    }

    Expression *expression() {
        return expression_;
    }

private:
    Designator *designator_;
    Expression *expression_;
};

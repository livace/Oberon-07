#pragma once

#include "terms.h"

#include "add_operator.h"
#include "term.h"

class TermOperation : public Terms {
public:
    TermOperation(Term* lhs, AddOperator* add_operator, Terms* rhs) : lhs_(lhs), add_operator_(add_operator), rhs_(rhs) {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

    Term* lhs() {
        return lhs_;
    }

    AddOperator* add_operator() {
        return add_operator_;
    }

    Terms* rhs() {
        return rhs_;
    }

private:
    Term* lhs_;
    AddOperator* add_operator_;
    Terms* rhs_;
};

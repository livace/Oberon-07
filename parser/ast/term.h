#pragma once

#include "ast.h"
#include "factor.h"
#include "mul_operator.h"

class Term : public Ast {
public:
    Term(Factor *factor, MulOperator *mul_operator = nullptr, Term *term = nullptr)
        : factor_(factor)
        , mul_operator_(mul_operator)
        , term_(term) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Factor* factor() {
        return factor_;
    }

    MulOperator *mulOperator() {
        return mul_operator_;
    }

    Term* term() {
        return term_;
    }

private:
    Factor* factor_;
    MulOperator *mul_operator_;
    Term* term_;
};

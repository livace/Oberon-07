#pragma once

#include "ast.h"

#include "terms.h"

#include "term.h"

class SingleTerm : public Terms {
public:
    SingleTerm(Term* term) : term_(term) {}

    Term* term() {
        return term_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    Term* term_;
};

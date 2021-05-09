#pragma once

#include "label.h"
#include "ast.h"

class LabelRange : public Ast {
public:
    LabelRange(Label *from, Label *to) : from_(from), to_(to) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Label *from() {
        return from_;
    }

    Label *to() {
        return to_;
    }

private:
    Label *from_;
    Label *to_;
};

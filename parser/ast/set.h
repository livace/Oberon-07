#pragma once

#include "ast.h"
#include "elements.h"

class Set : public Ast {
public:
    Set(Elements *elements) : elements_(elements) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Elements* elements() {
        return elements_;
    }

private:
    Elements* elements_;
};

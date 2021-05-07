#pragma once

#include "ast.h"
#include "element.h"

class Elements : public Ast {
public:
    Elements(Element *element, Elements *elements = nullptr) : element_(element), elements_(elements) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Element *element() {
        return element_;
    }

    Elements *elements() {
        return elements_;
    }

private:
    Element *element_;
    Elements *elements_;
};

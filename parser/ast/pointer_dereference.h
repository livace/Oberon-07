#pragma once

#include "selector.h"

class PointerDereference : public Selector {
public:
    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

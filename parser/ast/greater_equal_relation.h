#pragma once

#include "ast.h"

#include "relation.h"

class GreaterEqualRelation : public Relation {
public:
    GreaterEqualRelation() {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

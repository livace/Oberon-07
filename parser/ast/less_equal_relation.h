#pragma once

#include "ast.h"

#include "relation.h"

class LessEqualRelation : public Relation {
public:
    LessEqualRelation() {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

#pragma once

#include "ast.h"

#include "relation.h"

class LessRelation : public Relation {
public:
    LessRelation() {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

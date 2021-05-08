#pragma once

#include "ast.h"

#include "relation.h"

class EqualRelation : public Relation {
public:
    EqualRelation() {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

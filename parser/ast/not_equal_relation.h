#pragma once

#include "ast.h"

#include "relation.h"

class NotEqualRelation : public Relation {
public:
    NotEqualRelation() {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

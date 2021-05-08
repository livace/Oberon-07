#pragma once

#include "ast.h"

#include "relation.h"

class GreaterRelation : public Relation {
public:
    GreaterRelation() {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

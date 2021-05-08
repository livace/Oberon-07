#pragma once

#include "ast.h"

#include "relation.h"

class IsRelation : public Relation {
public:
    IsRelation() {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

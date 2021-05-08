#pragma once

#include "ast.h"

#include "relation.h"

class InRelation : public Relation {
public:
    InRelation() {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }
};

#pragma once

#include "qualident.h"
#include "ast.h"

class FormalType : public Ast {
public:
    FormalType(Qualident *qualident) : qualident_(qualident) {}

    void incArrayDepth() {
        ++array_depth;
    }

    Qualident *qualident() {
        return qualident_;
    }

    size_t arrayDepth() {
        return array_depth;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    size_t array_depth = 0;
    Qualident *qualident_;
};

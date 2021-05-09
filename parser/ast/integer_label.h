#pragma once

#include "ast.h"
#include "label.h"

class IntegerLabel : public Label {
public:
    IntegerLabel(int label) : label_(label) {}

    int label() {
        return label_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    int label_;
};

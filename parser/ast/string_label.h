#pragma once

#include "ast.h"
#include "label.h"

class StringLabel : public Label {
public:
    StringLabel(std::string label) : label_(std::move(label)) {}

    std::string label() {
        return label_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    std::string label_;
};

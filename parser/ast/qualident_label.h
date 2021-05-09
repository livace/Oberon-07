#pragma once

#include "qualident.h"
#include "label.h"
#include "ast.h"

class QualidentLabel : public Label {
public:
    QualidentLabel(Qualident *label) : label_(label) {}

    Qualident *label() {
        return label_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    Qualident *label_;
};

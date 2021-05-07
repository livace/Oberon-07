#pragma once

#include "qualident.h"
#include "type.h"
#include "ast.h"

class QualidentType : public Type {
public:
    QualidentType(Qualident *qualident) : qualident_(qualident) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Qualident *qualident() {
        return qualident_;
    }

private:
    Qualident *qualident_;
};

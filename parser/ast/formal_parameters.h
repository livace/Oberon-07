#pragma once

#include "fp_section_list.h"
#include "qualident.h"
#include "ast.h"

class FormalParameters : public Ast {
public:
    FormalParameters(FPSectionList *fp_section_list, Qualident *qualident)
        : fp_section_list_(fp_section_list)
        , qualident_(qualident) {}

    Qualident *qualident() {
        return qualident_;
    }

    FPSectionList *fpSectionList() {
        return fp_section_list_;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    FPSectionList *fp_section_list_;
    Qualident *qualident_;
};

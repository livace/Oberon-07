#pragma once

#include "fp_section.h"
#include "ast.h"

#include <vector>

class FPSectionList : public Ast {
public:
    FPSectionList(FPSection *fp_section) {
        fp_sections_.push_back(fp_section);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addFPSection(FPSection *fp_section) {
        fp_sections_.push_back(fp_section);
    }

    const std::vector<FPSection*>& FPSections() const {
        return fp_sections_;
    }

private:
    std::vector<FPSection*> fp_sections_;
};

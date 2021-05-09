#pragma once

#include "case.h"
#include "ast.h"

#include <vector>

class CaseList : public Ast {
public:
    CaseList(Case *case_value) {
        case_values_.push_back(case_value);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addCase(Case *case_value) {
        case_values_.push_back(case_value);
    }

    const std::vector<Case*>& cases() const {
        return case_values_;
    }

private:
    std::vector<Case*> case_values_;
};

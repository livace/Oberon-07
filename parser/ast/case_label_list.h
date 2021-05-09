#pragma once

#include "label_range.h"
#include "ast.h"

#include <vector>

class CaseLabelList : public Ast {
public:
    CaseLabelList(LabelRange *label_range) {
        label_ranges_.push_back(label_range);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addLabelRange(LabelRange *label_range) {
        label_ranges_.push_back(label_range);
    }

    const std::vector<LabelRange*>& labelRanges() const {
        return label_ranges_;
    }

private:
    std::vector<LabelRange*> label_ranges_;
};

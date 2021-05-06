#pragma once

#include "field_list.h"
#include "ast.h"

#include <vector>

class FieldListSequence : public Ast {
public:
    FieldListSequence(FieldList *field_list) {
        field_lists_.push_back(field_list);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addFieldList(FieldList *identdef) {
        field_lists_.push_back(identdef);
    }

    const std::vector<FieldList*>& fieldLists() const {
        return field_lists_;
    }

private:
    std::vector<FieldList*> field_lists_;
};

#pragma once

#include "base_type.h"
#include "field_list_sequence.h"
#include "ast.h"

class RecordType : public Type {
public:
    RecordType(BaseType *base_type, FieldListSequence *field_list_sequence)
        : base_type_(base_type)
        , field_list_sequence_(field_list_sequence) {}

    RecordType(FieldListSequence *field_list_sequence): field_list_sequence_(field_list_sequence) {}

    RecordType(BaseType *base_type) : base_type_(base_type) {}

    RecordType() {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    BaseType *baseType() {
        return base_type_;
    }

    FieldListSequence *fieldListSequence() {
        return field_list_sequence_;
    }

private:
    BaseType *base_type_{nullptr};
    FieldListSequence *field_list_sequence_{nullptr};
};

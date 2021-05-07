#pragma once

#include "formal_parameters.h"
#include "type.h"
#include "ast.h"

class ProcedureType : public Type {
public:
    ProcedureType(FormalParameters *formal_parameters)
        : formal_parameters_(formal_parameters) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    FormalParameters *formal_parameters() {
        return formal_parameters_;
    }

private:
    FormalParameters *formal_parameters_;
};

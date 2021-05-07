#pragma once

#include "identdef.h"
#include "formal_parameters.h"
#include "ast.h"

class ProcedureHeading : public Ast {
public:
    ProcedureHeading(IdentDef *identdef, FormalParameters *formal_parameters)
        : identdef_(identdef)
        , formal_parameters_(formal_parameters) {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

    IdentDef *identDef() {
        return identdef_;
    }

    FormalParameters *formalParameters() {
        return formal_parameters_;
    }

private:
    IdentDef *identdef_;
    FormalParameters *formal_parameters_;
};

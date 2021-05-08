#pragma once

#include "procedure_heading.h"
#include "procedure_body.h"
#include "identifier.h"
#include "ast.h"

#include <iostream>

class ProcedureDeclaration : public Ast {
public: 
    ProcedureDeclaration(ProcedureHeading *heading, ProcedureBody *body, Identifier *identifier)
        : heading_(heading)
        , body_(body)
        , identifier_(identifier) {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

    ProcedureHeading* procedureHeading() {
        return heading_;
    }

    ProcedureBody *body() {
        return body_;
    }

    Identifier *identifier() {
        return identifier_;
    }

private:
    ProcedureHeading* heading_;
    ProcedureBody *body_;
    Identifier *identifier_;
};

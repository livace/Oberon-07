#pragma once

#include "designator.h"
#include "actual_parameters.h"
#include "statement.h"

#include "ast.h"

class ProcedureCall : public Statement {
public:
    ProcedureCall(Designator *designator, ActualParameters *actual_parameters)
            : designator_(designator)
            , actual_parameters_(actual_parameters) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    Designator *designator() {
        return designator_;
    }

    ActualParameters *actualParameters() {
        return actual_parameters_;
    }

private:
    Designator *designator_;
    ActualParameters *actual_parameters_;
};

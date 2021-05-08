#pragma once

#include "ast.h"
#include "designator.h"
#include "actual_parameters.h"

class DesignatorFactor : public Factor {
public:
    DesignatorFactor(Designator *designator, ActualParameters *actual_parameters = nullptr) : set_(designator), actual_parameters_(actual_parameters) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    Designator *designator() {
        return set_;
    }
    
    ActualParameters *actualParameters() {
        return actual_parameters_;
    }

private:
    Designator *set_;
    ActualParameters *actual_parameters_;
};

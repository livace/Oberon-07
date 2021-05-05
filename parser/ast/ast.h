#pragma once

#include "parser/visitor/visitor.h"

class Ast {
public:
    virtual ~Ast() = default;
    virtual void accept(Visitor &visitor) = 0;
};

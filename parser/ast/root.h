#pragma once

#include "ast.h"
#include "module.h"

class Root : public Ast {
public:
    Root(Module *module) : module_(module) {}

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

    Module *module() {
        return module_;
    }

private:
    Module *module_;
};

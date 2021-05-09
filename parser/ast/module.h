#pragma once

#include "ast.h"

class Module : public Ast {
public:
    Module(Identifier *name, ImportList *import_list, DeclarationSequence *declarations,
            StatementSequence *statements, Identifier *end_name)
        : name_(name)
        , import_list_(import_list)
        , declarations_(declarations)
        , statements_(statements) {
        if (name->identifier() != end_name->identifier()) {
            throw std::runtime_error("Module names doesn't match");
        }
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

    Identifier *name() {
        return name_;
    }

    ImportList *importList() {
        return import_list_;
    }

    DeclarationSequence *declarations() {
        return declarations_;
    }

    StatementSequence *statements() {
        return statements_;
    }

private:
    Identifier *name_;
    ImportList *import_list_;
    DeclarationSequence *declarations_;
    StatementSequence *statements_;
};

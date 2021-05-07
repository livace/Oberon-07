#pragma once

#include "import_sequence.h"
#include "ast.h"

class ImportList : public Ast {
public:
    ImportList(ImportSequence *import_sequence) : import_sequence(std::move(import_sequence)) {}

    ImportSequence *importSequence() {
        return import_sequence;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(this);
    }

private:
    ImportSequence *import_sequence;
};

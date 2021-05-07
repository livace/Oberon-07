#pragma once

#include "import.h"
#include "ast.h"

#include <vector>

class ImportSequence : public Ast {
public:
    ImportSequence(Import *import) {
        imports_.push_back(import);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addImport(Import *import) {
        imports_.push_back(import);
    }

    const std::vector<Import*>& imports() const {
        return imports_;
    }

private:
    std::vector<Import*> imports_;
};

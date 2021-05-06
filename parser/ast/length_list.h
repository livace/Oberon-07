#pragma once

#include "length.h"
#include "ast.h"

#include <vector>

class LengthList : public Ast {
public:
    LengthList(Length *length) {
        lengths_.push_back(length);
    }

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }

    void addLength(Length *length) {
        lengths_.push_back(length);
    }

    const std::vector<Length*>& lengths() const {
        return lengths_;
    }

private:
    std::vector<Length*> lengths_;
};

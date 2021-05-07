#pragma once

#include "ast.h"
#include "string.h"

class StringFactor : public Factor {
public:
    StringFactor(String *string) : string_(string) {}

    void accept(Visitor &visitor) {
        visitor.visit(this);
    }    

    String* string() {
        return string_;
    }

private:
    String* string_;
};

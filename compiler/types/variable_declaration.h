#pragma once

#include <compiler/types/identifier.h>
#include <compiler/types/type.h>

class VariableDeclaration {
public:
    VariableDeclaration(Identifier *identifier, Type *type) {
        std::cout << "DECLARATION" << std::endl;
    }
private:

};
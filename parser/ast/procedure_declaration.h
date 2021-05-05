#pragma once

#include "ast.h"

#include <iostream>

class ProcedureDeclaration : public Ast {
public: 
    ProcedureDeclaration() {
        std::cerr << "Create ProcedureDeclaration Ast\n";
    }
};

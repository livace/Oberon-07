#pragma once

class ProcedureDeclaration;

class Visitor {
public:
    virtual void visit(ProcedureDeclaration *procedure_declaration) = 0; 
};

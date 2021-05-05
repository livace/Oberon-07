#pragma once

class ProcedureDeclaration;
class ProcedureHeading;

class Visitor {
public:
    virtual void visit(ProcedureDeclaration *procedure_declaration) = 0; 
    virtual void visit(ProcedureHeading *procedure_heading) = 0; 
};

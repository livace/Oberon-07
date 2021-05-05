#pragma once

class Identifier;
class ProcedureDeclaration;
class ProcedureHeading;
class Type;
class VariableDeclaration;

class Visitor {
public:
    virtual void visit(Identifier *procedure_heading) = 0; 
    virtual void visit(ProcedureDeclaration *procedure_declaration) = 0; 
    virtual void visit(ProcedureHeading *procedure_heading) = 0; 
    virtual void visit(Type *procedure_heading) = 0; 
    virtual void visit(VariableDeclaration *procedure_heading) = 0; 
};

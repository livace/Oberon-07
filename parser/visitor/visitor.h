#pragma once

class Identifier;
class ProcedureDeclaration;
class ProcedureHeading;
class Type;
class VariableDeclaration;
class Qualident;
class Root;
class Module;
class ConstDeclaration;
class ConstExpression;
class Expression;
class IdentDef;
class Number;
class String;

class Visitor {
public:
    virtual void visit(Identifier *procedure_heading) = 0; 
    virtual void visit(ProcedureDeclaration *procedure_declaration) = 0; 
    virtual void visit(ProcedureHeading *procedure_heading) = 0; 
    virtual void visit(Type *procedure_heading) = 0; 
    virtual void visit(VariableDeclaration *procedure_heading) = 0;
    virtual void visit(Qualident *qualident) = 0;
    virtual void visit(Root *root) = 0;
    virtual void visit(Module *module) = 0;
    virtual void visit(ConstDeclaration *const_declaration) = 0;
    virtual void visit(ConstExpression *const_expression) = 0;
    virtual void visit(Expression *expression) = 0;
    virtual void visit(IdentDef *identdef) = 0;
    virtual void visit(Number *number) = 0;
    virtual void visit(String *string) = 0;
};

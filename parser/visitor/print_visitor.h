#include "visitor.h"

#include <iostream>

#include <parser/ast/identifier.h>
#include <parser/ast/procedure_declaration.h>
#include <parser/ast/procedure_heading.h>
#include <parser/ast/type.h>
#include <parser/ast/variable_declaration.h>
#include <parser/ast/qualident.h>
#include <parser/ast/module.h>
#include <parser/ast/const_declaration.h>
#include <parser/ast/const_expression.h>
#include <parser/ast/expression.h>
#include <parser/ast/identdef.h>
#include <parser/ast/number.h>
#include <parser/ast/string.h>
#include <parser/ast/root.h>

class PrintVisitor : public Visitor {
    void visit(Identifier *identifier) override {
        std::cerr << identifier->identifier();
    }  

    void visit(ProcedureDeclaration *procedure_declaration) override {
        std::cerr << "PROCEDURE";
        procedure_declaration->procedureHeading()->accept(*this);
    }

    void visit(ProcedureHeading *procedure_heading) override {
        std::cerr << "<some name>";
    }  

<<<<<<< HEAD
    void visit(Type *type) {
        std::cerr << "type";
=======
    void visit(Type *type) override {
        std::cerr << type->name();
>>>>>>> More classes
    }  

    void visit(VariableDeclaration *variable_declaration) override {
        variable_declaration->identifier()->accept(*this);
        std::cerr << ":";
        variable_declaration->type()->accept(*this);
    }

    void visit(Qualident *qualident) override {
        if (auto prefix = qualident->prefix(); prefix) {
            prefix->accept(*this);
        }
        qualident->identifier()->accept(*this);
    }

    void visit(Module *module) override {
    }

    void visit(ConstDeclaration *const_declaration) override {
        const_declaration->identifier()->accept(*this);
        const_declaration->constExpression()->accept(*this);
    }

    void visit(ConstExpression *const_expression) override {
        const_expression->expression()->accept(*this);
    }

    void visit(Expression *expression) override {
    }

    void visit(IdentDef *identdef) override {
        std::cerr << identdef->identifier() << ", is_exported: " << identdef->isExported();
    }

    void visit(Number *number) override {
        std::cerr << number->float_value();
    }

    void visit(String *string) override {
        std::cerr << string->value();
    }

    void visit(Root *root) override {
        root->module()->accept(*this);
    }

    void visit(ArrayType *array_type) {

    }

    void visit(BaseType *base_type) {

    }

    void visit(FieldList *field_list) {

    }

    void visit(FieldListSequence *field_list_sequence) {

    }

    void visit(IdentList *ident_list) {

    }

    void visit(Integer *integer) {

    }

    void visit(Length *length) {

    }

    void visit(LengthList *length_list) {

    }

    void visit(PointerType *pointer_type) {

    }

    void visit(QualidentType *qualident_type) {

    }

    void visit(Real *real) {

    }

    void visit(RecordType *record_type) {

    }

    void visit(TypeDeclaration *type_declaration) {

    }

    void visit(BinaryMinus *binary_minus) override {
        std::cerr << "-";
    }
    
    void visit(BinaryPlus *binary_plus) override {
        std::cerr << "+";
    }
    
    void visit(Division *division) override {
        std::cerr << "/";
    }
    
    void visit(IntegerDivision *integer_division) override {
        std::cerr << "//";
    }
    
    void visit(LogicalConjunction *logical_conjuction) override {
        std::cerr << "&";
    }
    
    void visit(LogicalDisjunction *logical_disjunction) override {
        std::cerr << "|";
    }

    void visit(Modulo *modulo) override {
        std::cerr << "%";
    }
    
    void visit(Multiplication *multimplication) override {
        std::cerr << "*";
    }

    void visit(SimpleExpression *simple_expression) override {
        std::cerr << "&";
    }

    void visit(SingleTerm *single_term) override {
        single_term->term()->accept(*this);
    }

    void visit(Term *term) override {
        std::cerr << "<term>"; // TODO
    }

    void visit(TermOperation *term_operation) override {
        term_operation->lhs()->accept(*this);
        std::cerr << " ";
        term_operation->add_operator()->accept(*this);
        std::cerr << " ";
        term_operation->rhs()->accept(*this);
    }

    void visit(UnaryMinus *unary_minus) override {
        std::cerr << "-";
    }

    void visit(UnaryPlus *unary_plus) override {
        std::cerr << "+";
    }
};

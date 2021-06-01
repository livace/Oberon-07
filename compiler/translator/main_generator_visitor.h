#pragma once

#include "parser/visitor/visitor.h"

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
#include <parser/ast/integer.h>
#include <parser/ast/real.h>
#include <parser/ast/string.h>
#include <parser/ast/root.h>
#include <parser/ast/add_operator.h>
#include <parser/ast/binary_minus.h>
#include <parser/ast/binary_plus.h>
#include <parser/ast/binary_minus.h>
#include <parser/ast/division.h>
#include <parser/ast/integer_division.h>
#include <parser/ast/logical_conjunction.h>
#include <parser/ast/logical_disjunction.h>
#include <parser/ast/modulo.h>
#include <parser/ast/mul_operator.h>
#include <parser/ast/multiplication.h>
#include <parser/ast/simple_expression.h>
#include <parser/ast/single_term.h>
#include <parser/ast/term.h>
#include <parser/ast/term_operation.h>
#include <parser/ast/terms.h>
#include <parser/ast/unary_minus.h>
#include <parser/ast/unary_plus.h>
#include <parser/ast/exp_list.h>
#include <parser/ast/field_selector.h>
#include <parser/ast/array_selector.h>
#include <parser/ast/pointer_dereference.h>
#include <parser/ast/selectors.h>
#include <parser/ast/designator.h>
#include <parser/ast/expression_factor.h>
#include <parser/ast/negation_factor.h>
#include <parser/ast/case.h>
#include <parser/ast/case_statement.h>
#include <parser/ast/elsif_while_list.h>
#include <parser/ast/for_statement.h>
#include <parser/ast/integer_label.h>
#include <parser/ast/qualident_label.h>
#include <parser/ast/repeat_statement.h>
#include <parser/ast/string_label.h>
#include <parser/ast/while_statement.h>
#include <cmath>
#include <set>

class MainGeneratorVisitor : public Visitor {
public:

    template <class T>
    void go(T *node) {
        if (node) {
            node->accept(*this);
        }
    }

    void visit(Identifier *identifier) override {}
    void visit(ProcedureDeclaration *procedure_declaration) override {} 
    void visit(ProcedureHeading *procedure_heading) override {} 
    void visit(VariableDeclaration *variable_declaration) override {}
    void visit(Qualident *qualident) override {}
    void visit(Root *root) override {
        out_ = std::ofstream(root->module()->name()->identifier() + ".cpp");
        go(root->module());
    }
    
    void visit(Module *module) override {
        out_ << "#include \"" << module->name()->identifier() << ".h\"\n";
        out_ << "int main() { " << "__" << module->name()->identifier() << "__::" << module->name()->identifier()  << ".main(); " << "}";
    }

    void visit(ConstDeclaration *const_declaration) override {}
    void visit(ConstExpression *const_expression) override {}
    void visit(Expression *expression) override {}
    void visit(IdentDef *identdef) override {}
    void visit(Number *number) override {}
    void visit(String *string) override {}
    void visit(ArrayType *array_type) override {}
    void visit(BaseType *base_type) override {}
    void visit(FieldList *field_list) override {}
    void visit(FieldListSequence *field_list_sequence) override {}
    void visit(IdentDefList *ident_list) override {}
    void visit(Integer *integer) override {}
    void visit(Length *length) override {}
    void visit(LengthList *length_list) override {}
    void visit(PointerType *pointer_type) override {}
    void visit(QualidentType *qualident_type) override {}
    void visit(Real *real) override {}
    void visit(RecordType *record_type) override {}
    void visit(TypeDeclaration *type_declaration) override {}
    void visit(BinaryMinus *binary_minus) override {}
    void visit(BinaryPlus *binary_plus) override {}
    void visit(Division *division) override {}
    void visit(IntegerDivision *integer_division) override {}
    void visit(LogicalConjunction *logical_conjunction) override {}
    void visit(LogicalDisjunction *logical_disjunction) override {}
    void visit(Modulo *modulo) override {}
    void visit(Multiplication *multiplication) override {}
    void visit(SimpleExpression *simple_expression) override {}
    void visit(SingleTerm *single_term) override {}
    void visit(Term *term) override {}
    void visit(TermOperation *term_operation) override {}
    void visit(UnaryMinus *unary_minus) override {}
    void visit(UnaryPlus *unary_plus) override {}
    void visit(FormalParameters *formal_parameters) override {}
    void visit(FormalType *formal_type) override {}
    void visit(FPSection *fp_section) override {}
    void visit(FPSectionList *fp_section_list) override {}
    void visit(IdentifierList *identifier_list) override {}
    void visit(ProcedureType *procedure_type) override {}
    void visit(VariableDeclarationList *variable_declaration_list) override {}
    void visit(ConstDeclarationList *const_declaration_list) override {}
    void visit(DeclarationSequence *declaration_sequence) override {}
    void visit(Import *import) override {}
    void visit(ImportList *import_list) override {}
    void visit(ImportSequence *import_sequence) override {}
    void visit(ProcedureDeclarationList *procedure_declaration_list) override {}
    void visit(TypeDeclarationList *type_declaration_list) override {}
    void visit(NumberFactor* number_factor) override {}
    void visit(StringFactor* string_factor) override {}
    void visit(NilFactor* nil_factor) override {}
    void visit(TrueFactor* true_factor) override {}
    void visit(FalseFactor* false_factor) override {}
    void visit(Elements* elements) override {} 
    void visit(Range* range) override {} 
    void visit(Set* set) override {} 
    void visit(SetFactor* set_factor) override {} 
    void visit(SingleElement* single_element) override {} 
    void visit(ExpList* exp_list) override {} 
    void visit(ActualParameters* actual_parameters) override {} 
    void visit(FieldSelector *field_selector) override {}
    void visit(ArraySelector *array_selector) override {}
    void visit(PointerDereference *pointer_dereference) override {}    
    void visit(Selectors *selectors) override {}
    void visit(Designator *designator) override {}
    void visit(DesignatorFactor *designator_factor) override {}
    void visit(ExpressionFactor *expression_factor) override {}
    void visit(NegationFactor *negation_factor) override {}
    void visit(EqualRelation *equal_relation) override {}
    void visit(NotEqualRelation *not_equal_relation) override {}
    void visit(LessRelation *less_relation) override {}
    void visit(LessEqualRelation *less_equal_relation) override {} 
    void visit(GreaterRelation *greater_relation) override {}  
    void visit(GreaterEqualRelation *greater_equal_relation) override {}   
    void visit(InRelation *in_relation) override {}    
    void visit(IsRelation *is_relation) override {}
    void visit(Assignment *assignment) override {}
    void visit(ElsifList *elsif_list) override {}
    void visit(IfStatement *if_statement) override {}
    void visit(ProcedureBody *procedure_body) override {}
    void visit(ProcedureCall *procedure_call) override {}
    void visit(StatementSequence *statement_sequence) override {}
    void visit(Case *case_node) override {}
    void visit(CaseLabelList *case_label_list) override {}
    void visit(CaseList *case_list) override {}
    void visit(CaseStatement *case_statement) override {}
    void visit(ElsifWhileList *elsif_while_list) override {}
    void visit(ForStatement *for_statement) override {}
    void visit(IntegerLabel *integer_label) override {}
    void visit(LabelRange *label_range) override {}
    void visit(QualidentLabel *qualident_label) override {}
    void visit(RepeatStatement *repeat_statement) override {}
    void visit(StringLabel *string_label) override {}
    void visit(WhileStatement *while_statement) override {}

private:
    std::ofstream out_;
};

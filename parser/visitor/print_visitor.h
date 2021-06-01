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

class PrintVisitor : public Visitor {
    template <class T>
    void go(T *node) {
        if (node) {
            node->accept(*this);
        }
    }

    void visit(Identifier *identifier) override {
        std::cerr << identifier->identifier();
    }  

    void visit(ProcedureDeclaration *procedure_declaration) override {
        std::cerr << "PROCEDURE ";
        go(procedure_declaration->procedureHeading());
        std::cerr << ";";
        std::cerr << "\n";
        go(procedure_declaration->body());
        std::cerr << "\n";
        go(procedure_declaration->identifier());
    }

    void visit(ProcedureHeading *procedure_heading) override {
        go(procedure_heading->identDef());
        go(procedure_heading->formalParameters());
    }  

    void visit(VariableDeclaration *variable_declaration) override {
        go(variable_declaration->identList());
        std::cerr << ":";
        go(variable_declaration->type());
    }

    void visit(Qualident *qualident) override {
        if (qualident->prefix()) {
            go(qualident->prefix());
            std::cerr << ".";
        }

        go(qualident->identifier());
    }

    void visit(Module *module) override {
        std::cerr << "MODULE ";
        go(module->name());
        std::cerr << ";";
        if (module->importList()) {
            std::cerr << "\n";
            go(module->importList());
        }
        std::cerr << "\n";
        go(module->declarations());
        if (module->statements()) {
            std::cerr << "BEGIN\n";
            go(module->statements());
        }
        std::cerr << "\n";
        std::cerr << "END ";
        go(module->name());
        std::cerr << ".";
    }

    void visit(ConstDeclaration *const_declaration) override {
        go(const_declaration->identifier());
        std::cerr << " = ";
        go(const_declaration->constExpression());
    }

    void visit(ConstExpression *const_expression) override {
        go(const_expression->expression());
    }

    void visit(Expression *expression) override {
        go(expression->primary());
        if (expression->relation()) {
            std::cerr << " ";
            go(expression->relation());
            std::cerr << " ";
            go(expression->secondary());
        }
    }

    void visit(IdentDef *identdef) override {
        std::cerr << identdef->identifier();
        if (identdef->isExported()) {
            std::cerr << " *";
        }
    }

    void visit(Number *number) override {
        std::cerr << number->float_value();
    }

    void visit(String *string) override {
        std::cerr << string->value();
    }

    void visit(Root *root) override {
        go(root->module());
    }

    void visit(ArrayType *array_type) {
        std::cerr << "ARRAY ";
        go(array_type->lengths());
        std::cerr << " OF ";
        go(array_type->type());
    }

    void visit(BaseType *base_type) {
        go(base_type->qualident());
    }

    void visit(FieldList *field_list) {
        go(field_list->identList());
        go(field_list->type());
    }

    void visit(FieldListSequence *field_list_sequence) {
        for (auto& field_list : field_list_sequence->fieldLists()) {
            go(field_list);
        }
    }

    void visit(IdentDefList *ident_list) {
        bool first = true;
        for (auto& identdef : ident_list->identdefs()) {
            if (!first) {
                std::cerr << ", ";
            }
            first = false;
            go(identdef);
        }
    }

    void visit(Integer *integer) {
        std::cerr << integer->value();
    }

    void visit(Length *length) {
        go(length->constExpression());
    }

    void visit(LengthList *length_list) {
        bool is_first = true;
        for (auto& length : length_list->lengths()) {
            if (!is_first) {
                std::cout << ", ";
            }
            go(length);
            is_first = false;
        }
    }

    void visit(PointerType *pointer_type) {
        std::cerr << "POINTER TO ";
        go(pointer_type->type());
    }

    void visit(QualidentType *qualident_type) {
        go(qualident_type->qualident());
    }

    void visit(Real *real) {
        std::cerr << real->value();
    }

    void visit(RecordType *record_type) {
        std::cerr << "RECORD";
        if (record_type->baseType()) {
            std::cerr << " (";
            go(record_type->baseType());
            std::cerr << ")";
        }
        if (record_type->fieldListSequence()) {
            std::cerr << " ";
            go(record_type->fieldListSequence());
        }
        std::cerr << " END";
    }

    void visit(TypeDeclaration *type_declaration) {
        go(type_declaration->identDef());
        std::cerr << "=";
        go(type_declaration->type());
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
        std::cerr << "DIV";
    }
    
    void visit(LogicalConjunction *logical_conjunction) override {
        std::cerr << "&";
    }
    
    void visit(LogicalDisjunction *logical_disjunction) override {
        std::cerr << "OR";
    }

    void visit(Modulo *modulo) override {
        std::cerr << "MOD";
    }
    
    void visit(Multiplication *multiplication) override {
        std::cerr << "*";
    }

    void visit(SimpleExpression *simple_expression) override {
        go(simple_expression->unaryOperator());
        go(simple_expression->terms());
    }

    void visit(SingleTerm *single_term) override {
        go(single_term->term());
    }

    void visit(Term *term) override {
        go(term->factor());
        if (term->mulOperator()) {
            std::cerr << " ";
            go(term->mulOperator());
            std::cerr << " ";
            go(term->term());
        }
    }

    void visit(TermOperation *term_operation) override {
        go(term_operation->lhs());
        std::cerr << " ";
        go(term_operation->add_operator());
        std::cerr << " ";
        go(term_operation->rhs());
    }

    void visit(UnaryMinus *unary_minus) override {
        std::cerr << "-";
    }

    void visit(UnaryPlus *unary_plus) override {
        std::cerr << "+";
    }

    void visit(FormalParameters *formal_parameters) override {
        std::cerr << "(";
        go(formal_parameters->fpSectionList());
        std::cerr << ")";
        
        if (formal_parameters->qualident()) {
            std::cerr << ":";
            go(formal_parameters->qualident());
        }
    };

    void visit(FormalType *formal_type) override {
        for (size_t i = 0; i < formal_type->arrayDepth(); ++i) {
            std::cerr << "ARRAY OF ";
        }
        go(formal_type->qualident());
    };

    void visit(FPSection *fp_section) override {
        if (fp_section->isVariable()) {
            std::cerr << "VAR ";
        }
        go(fp_section->identifierList());
        std::cerr << " : ";
        go(fp_section->formalType());
    };

    void visit(FPSectionList *fp_section_list) override {
        bool first = true;
        for (auto& fp_section : fp_section_list->FPSections()) {
            if (!first) {
                std::cerr << ";\n";
            }
            first = false;
            go(fp_section);
        }
    };

    void visit(IdentifierList *identifier_list) override {
        bool first = true;
        for (auto& identifier : identifier_list->identifiers()) {
            if (!first) {
                std::cerr << ", ";
            }
            first = false;
            go(identifier);
        }
    };

    void visit(ProcedureType *procedure_type) override {
        std::cerr << "PROCEDURE ";
        go(procedure_type->formal_parameters());
    };

    void visit(VariableDeclarationList *variable_declaration_list) override {
        bool first = true;
        for (auto& variable_declaration : variable_declaration_list->variableDeclarations()) {
            if (!first) {
                std::cerr << "\n";
            }
            first = false;
            go(variable_declaration);
            std::cerr << ";";
        }
    };

    void visit(ConstDeclarationList *const_declaration_list) {
        for (auto& const_declaration : const_declaration_list->constDeclarations()) {
            go(const_declaration);
            std::cerr << ";\n";
        }
    }

    void visit(DeclarationSequence *declaration_sequence) {
        bool first = true;
        if (declaration_sequence->constDeclarationList()) {
            first = false;
            std::cerr << "CONST ";
            go(declaration_sequence->constDeclarationList());
        }
        
        if (declaration_sequence->variableDeclarationList()) {
            if (!first) {
                std::cerr << " ";
            }
            first = false;
            std::cerr << "VAR ";
            go(declaration_sequence->variableDeclarationList());
        }

        if (declaration_sequence->typeDeclarationList()) {
            if (!first) {
                std::cerr << " ";
            }
            first = false;
            std::cerr << "TYPE ";
            go(declaration_sequence->typeDeclarationList());
        }
        
        if (!first) {
            std::cerr << "\n";
        }
        first = false;
        go(declaration_sequence->procedureDeclarationList());
    }

    void visit(Import *import) {
        go(import->identifier());
        go(import->alias());
    }

    void visit(ImportList *import_list) {
        go(import_list->importSequence());
    }

    void visit(ImportSequence *import_sequence) {
        for (auto& import : import_sequence->imports()) {
            go(import);
            std::cerr << ";\n";
        }
    }

    void visit(ProcedureDeclarationList *procedure_declaration_list) {
        for (auto& procedure_declaration : procedure_declaration_list->procedureDeclarations()) {
            go(procedure_declaration);
            std::cerr << ";\n";
        }
    }

    void visit(TypeDeclarationList *type_declaration_list) {
        for (auto& type_declaration : type_declaration_list->typeDeclarations()) {
            go(type_declaration);
            std::cerr << ";\n";
        }
    }

    void visit(NumberFactor* number_factor) override {
        go(number_factor->number());    
    }

    void visit(StringFactor* string_factor) override {
        go(string_factor->string());    
        
    }

    void visit(NilFactor* nil_factor) override {
        std::cerr << "NIL";   
    }

    void visit(TrueFactor* true_factor) override {
        std::cerr << "TRUE";   
    }

    void visit(FalseFactor* false_factor) override {   
        std::cerr << "FALSE";   
    }

    void visit(Elements* elements) override {
        go(elements->element());

        if (elements->elements()) {
            std::cerr << ", ";
            go(elements);
        }
    }

    void visit(Range* range) override {
        go(range->from());
        if (range->to()) {
            std::cerr << "..";
            go(range->to());
        }
    }

    void visit(Set* set) override {
        go(set->elements());
    }

    void visit(SetFactor* set_factor) override {
        go(set_factor->set());
    }

    void visit(SingleElement* single_element) override {
        go(single_element->expression());
    }

    void visit(ExpList* exp_list) override {
        go(exp_list->expression());
        if (exp_list->expList()) {
            std::cerr << ", ";
            go(exp_list->expList());
        }
    } 

    void visit(ActualParameters* actual_parameters) override {
        std::cerr << "(";
        go(actual_parameters->expList());
        std::cerr << ")";
    }

    void visit(FieldSelector *field_selector) override {
        std::cerr << ".";
        go(field_selector->ident());
    }

    void visit(ArraySelector *array_selector) override {
        std::cerr << "[";
        go(array_selector->exp_list());
        std::cerr << "]";
    }

    void visit(PointerDereference *pointer_dereference) override {
        std::cerr << "^";
    }   

    void visit(Selectors *selectors) override {
        go(selectors->selector());
        if (selectors->selectors()) {
            std::cerr << " ";
            go(selectors->selectors());
        }
    }

    void visit(Designator *designator) override {
        go(designator->qualident());
        go(designator->selectors());
    }

    void visit(ExpressionFactor *expression_factor) override {
        std::cerr << "(";
        go(expression_factor->expression());
        std::cerr << ")";
    }

    void visit(NegationFactor *negation_factor) override {
        std::cerr << "~";
        go(negation_factor->factor());
    }

    void visit(DesignatorFactor *designator_factor) override {
        go(designator_factor->designator());
        go(designator_factor->actualParameters());
    }

    void visit(EqualRelation *equal_relation) override {
        std::cerr << "=";
    }

    void visit(NotEqualRelation *not_equal_relation) override {
        std::cerr << "#";
    }

    void visit(LessRelation *less_relation) override {
        std::cerr << "<";
    }

    void visit(LessEqualRelation *less_equal_relation) override {
        std::cerr << "<=";
    }

    void visit(GreaterRelation *greater_relation) override {
        std::cerr << ">";
    }

    void visit(GreaterEqualRelation *greater_equal_relation) override {
        std::cerr << ">=";
    }

    void visit(InRelation *in_relation) override {
        std::cerr << "IN";
    }

    void visit(IsRelation *is_relation) override {
        std::cerr << "IS";
    }

    void visit(Assignment *assignment) override {
        go(assignment->designator());
        std::cerr << " := ";
        go(assignment->expression());
    }

    void visit(ElsifList *elsif_list) override {
        std::cerr << "ELSIF ";
        go(elsif_list->expression());
        std::cerr << "\nTHEN ";
        go(elsif_list->statementSequence());
        go(elsif_list->elsifList());
    }

    void visit(IfStatement *if_statement) override {
        std::cerr << "IF ";
        go(if_statement->expression());
        std::cerr << "\nTHEN\n";
        go(if_statement->thenStatements());
        if (if_statement->elsifList()) {
            std::cerr << "\n";
            go(if_statement->elsifList());
            std::cerr << "\n";
        }
        if (if_statement->elseStatements()) {
            std::cerr << "\nELSE\n";
            go(if_statement->elseStatements());
        }
        std::cerr << "\nEND";
    }

    void visit(ProcedureBody *procedure_body) override {
        go(procedure_body->declarationSequence());
        if (procedure_body->body()) {
            std::cerr << "BEGIN\n";
            go(procedure_body->body());
        }
        if (procedure_body->returnExpression()) {
            std::cerr << "RETURN ";
            go(procedure_body->returnExpression());
        }
        std::cerr << "\nEND";
    }

    void visit(ProcedureCall *procedure_call) override {
        go(procedure_call->designator());
        if (procedure_call->actualParameters()) {
            go(procedure_call->actualParameters());
        }
    }

    void visit(StatementSequence *statement_sequence) override {
        bool first = true;
        for (Statement* statement : statement_sequence->statements()) {
            if (!first) {
                std::cerr << ";";
                std::cerr << "\n";
            }
            first = false;
            go(statement);
        }
    }

    void visit(Case *case_node) override {
        go(case_node->labelList());
        std::cerr << ": ";
        go(case_node->statementSequence());
    }

    void visit(CaseLabelList *case_label_list) override {
        bool first = true;
        for (LabelRange *label_range : case_label_list->labelRanges()) {
            if (!first) {
                std::cerr << ", ";
            }
            first = false;
            go(label_range);
        }
    }

    void visit(CaseList *case_list) override {
        bool first = true;
        for (Case *case_node : case_list->cases()) {
            if (!first) {
                std::cerr << "\n| ";
            } else {
                std::cerr << "  ";
            }
            first = false;
            go(case_node);
        }
    }

    void visit(CaseStatement *case_statement) override {
        std::cerr << "CASE ";
        go(case_statement->expression());
        std::cerr << "OF\n";
        go(case_statement->cases());
        std::cerr << "\nEND";
    }

    void visit(ElsifWhileList *elsif_while_list) override {
        std::cerr << "ELSIF";
        go(elsif_while_list->expression());
        std::cerr << "\n";
        std::cerr << "DO";
        std::cerr << "\n";
        go(elsif_while_list->statementSequence());
        
        if (elsif_while_list->elsifWhileList()) {
            std::cerr << "\n";
            go(elsif_while_list->elsifWhileList());
        }
    }

    void visit(ForStatement *for_statement) override {
        std::cerr << "FOR ";
        go(for_statement->variableName());
        std::cerr << " := ";
        go(for_statement->variableExpression());
        std::cerr << " TO ";
        go(for_statement->toExpression());
        if (for_statement->byExpression()) {
            std::cerr << " BY ";
            go(for_statement->byExpression());        
        }
        std::cerr << "\n";
        std::cerr << "DO";
        std::cerr << "\n";
        go(for_statement->body());
        std::cerr << "\n";
        std::cerr << "END";
    }

    void visit(IntegerLabel *integer_label) override {
        std::cerr << integer_label->label();
    }

    void visit(LabelRange *label_range) override {
        go(label_range->from());
        std::cerr << "..";
        go(label_range->to());
    }

    void visit(QualidentLabel *qualident_label) override {
        go(qualident_label->label());
    }

    void visit(RepeatStatement *repeat_statement) override {
        std::cerr << "REPEAT";
        std::cerr << "\n";
        go(repeat_statement->body());
        std::cerr << "\n";
        std::cerr << "UNTIL ";
        go(repeat_statement->expression());
    }

    void visit(StringLabel *string_label) override {
        std::cerr << string_label->label();
    }

    void visit(WhileStatement *while_statement) override {
        std::cerr << "WHILE ";
        go(while_statement->expression());
        std::cerr << "\n";
        std::cerr << "DO";
        std::cerr << "\n";
        go(while_statement->body());
        if (while_statement->elseList()) {
            std::cerr << "\n";
            go(while_statement->elseList());
        }
        std::cerr << "\n";
        std::cerr << "END";
    }
};

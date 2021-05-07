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
        std::cerr << "PROCEDURE";
        go(procedure_declaration->procedureHeading());
    }

    void visit(ProcedureHeading *procedure_heading) override {
        std::cerr << "<some name>";
    }  

    void visit(Type *type) override {
        std::cerr << "<type>";
    }

    void visit(VariableDeclaration *variable_declaration) override {
        go(variable_declaration->identList());
        std::cerr << ":";
        go(variable_declaration->type());
    }

    void visit(Qualident *qualident) override {
        go(qualident->prefix());
        go(qualident->identifier());
    }

    void visit(Module *module) override {
    }

    void visit(ConstDeclaration *const_declaration) override {
        go(const_declaration->identifier());
        go(const_declaration->constExpression());
    }

    void visit(ConstExpression *const_expression) override {
        go(const_expression->expression());
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
        go(root->module());
    }

    void visit(ArrayType *array_type) {
        go(array_type->lengths());
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
        for (auto& identdef : ident_list->identdefs()) {
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
        for (auto& length : length_list->lengths()) {
            go(length);
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
        std::cerr << "RECORD ";
        go(record_type->baseType());
        go(record_type->fieldListSequence());
        std::cerr << "END";
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
        std::cerr << "//";
    }
    
    void visit(LogicalConjunction *logical_conjunction) override {
        std::cerr << "&";
    }
    
    void visit(LogicalDisjunction *logical_disjunction) override {
        std::cerr << "|";
    }

    void visit(Modulo *modulo) override {
        std::cerr << "%";
    }
    
    void visit(Multiplication *multiplication) override {
        std::cerr << "*";
    }

    void visit(SimpleExpression *simple_expression) override {
        std::cerr << "&";
    }

    void visit(SingleTerm *single_term) override {
        go(single_term->term());
    }

    void visit(Term *term) override {
        std::cerr << "<term>"; // TODO
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
        go(formal_parameters->fpSectionList());
        go(formal_parameters->qualident());
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
        for (auto& fp_section : fp_section_list->FPSections()) {
            go(fp_section);
            std::cerr << ";\n";
        }
    };

    void visit(IdentifierList *identifier_list) override {
        for (auto& identifier : identifier_list->identifiers()) {
            go(identifier);
            std::cerr << ", ";
        }
    };

    void visit(ProcedureType *procedure_type) override {
        std::cerr << "PROCEDURE ";
        go(procedure_type->formal_parameters());
    };

    void visit(VariableDeclarationList *variable_declaration_list) override {
        for (auto& variable_declaration : variable_declaration_list->variableDeclarations()) {
            go(variable_declaration);
            std::cerr << ";\n";
        }
    };

    void visit(ConstDeclarationList *const_declaration_list) {
        for (auto& const_declaration : const_declaration_list->constDeclarations()) {
            go(const_declaration);
            std::cerr << ";\n";
        }
    }

    void visit(DeclarationSequence *declaration_sequence) {
        go(declaration_sequence->constDeclarationList());
        go(declaration_sequence->variableDeclarationList());
        go(declaration_sequence->typeDeclarationList());
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
};

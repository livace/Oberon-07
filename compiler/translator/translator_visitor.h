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

class TranslatorVisitor : public Visitor {
public:
    template <class T>
    void go(T *node) {
        if (node) {
            node->accept(*this);
        }
    }

    void visit(Identifier *identifier) override {
        out_ << identifier->identifier();
    }

    void visit(ProcedureDeclaration *procedure_declaration) override {
        go(procedure_declaration->procedureHeading());
        out_ << "{\n";
        go(procedure_declaration->body());
        out_ << "}\n\n";
    }

    void getReturnType(Qualident *return_type) {
        if (return_type != nullptr) {
            qualidentToString(return_type);
        } else {
            out_ << "void";
        }
    }

    void visit(ProcedureHeading *procedure_heading) override {
        getReturnType(procedure_heading->getProcedureReturnType());
        out_ << " ";
        go(procedure_heading->identDef());
        out_ << "(";
        go(procedure_heading->formalParameters());
        out_ << " )";
    }

    void addIdentTypes(IdentDefList *list, Type *type) {
        for (const auto& identdef : list->identdefs()) {
            variable_types[identdef->identifier()] = type;
        }
    }

    bool isVariablePointer(const std::string& name) {
        auto type = variable_types[name];
        if (!type) {
            return false;
        }
        if (dynamic_cast<PointerType*>(type)) {
            return true;
        }
        if (auto qualident_type = dynamic_cast<QualidentType*>(type); qualident_type) {
            return is_pointer_qualident[qualident_type->qualident()->identifier()->identifier()];
        }
        return false;
    }

    void visit(VariableDeclaration *variable_declaration) override {
        addIdentTypes(variable_declaration->identList(), variable_declaration->type());
        go(variable_declaration->type());
        out_ << " ";
        if (auto array_type = dynamic_cast<ArrayType*>(variable_declaration->type()); array_type) {
            bool is_first = true;
            for (const auto& identdef : variable_declaration->identList()->identdefs()) {
                if (!is_first) {
                    out_ << ", ";
                }
                go(identdef);
                createVectorConstruction(array_type);
                is_first = false;
            }
        } else {
            go(variable_declaration->identList());
        }
        out_ << ";\n";
    }

    void visit(Qualident *qualident) override {
        if (qualident->prefix()) {
            go(qualident->prefix());
            out_ << ".";
        }
        go(qualident->identifier());
    }

    void visit(Root *root) override {
        out_ = std::ofstream(root->module()->name()->identifier() + ".h");

        out_ << "#pragma once\n";
        out_ << "#include \"Lib.h\"\n";
        go(root->module());
    }

    void visit(Module *module) override {
        go(module->importList());

        inside_namespace_ = true;
        out_ << "namespace __" << module->name()->identifier() << "__ {";

        go(module->importList());

        go(module->declarations());

        out_ << "class __" << module->name()->identifier() << "__ {\n";
        out_ << "public:";

        if (module->statements()) {
            out_ << "void main() { ";
            go(module->statements());
            out_ << " }";
        }
        out_ << "\n} " << module->name()->identifier() << ";";
        out_ << "}";
    }

    void visit(ConstDeclaration *const_declaration) override {
        out_ << "const auto ";
        go(const_declaration->identifier());
        out_ << " = ";
        go(const_declaration->constExpression());
        out_ << ";\n";
    }

    void visit(ConstExpression *const_expression) override {
        go(const_expression->expression());
    }

    void visit(Expression *expression) override {
        go(expression->primary());
        if (expression->relation()) {
            out_ << " ";
            go(expression->relation());
            out_ << " ";
            go(expression->secondary());
        }
    }

    void visit(IdentDef *identdef) override {
        out_ << identdef->identifier();
    }

    void visit(Real *number) override {
        out_ << number->value();
    }

    void visit(Integer *number) override {
        out_ << number->value();
    }

    void visit(String *string) override {
        out_ << string->value();
    }

    bool createVectorOfVectors(size_t size, Type *type) {
        if (size == 0) {
            go(type);
            return false;
        }
        if (size >= 1) {
            out_ << "std::vector<";
            createVectorOfVectors(size - 1, type);
            out_ << ">";
        }
        return true;
    }

    void createVectorConstruction(ArrayType *array_type) {
        out_ << "(";
        size_t size = array_type->lengths()->lengths().size();
        Type *type = array_type->type();
        auto& lengths = array_type->lengths()->lengths();
        for (auto it = lengths.rbegin(); it != lengths.rend(); ++it) {
            go(*it);
            out_ <<", ";
            if (size != 1) {
                if (createVectorOfVectors(--size, type)) {
                    out_ << "(";
                }
            }
        }
        size = array_type->lengths()->lengths().size();
        out_ << "0)";
        out_ << std::string(size - 1, ')');
    }

    void visit(Number *number) override {
        out_ << number->float_value();
    }

    void visit(ArrayType *array_type) override {
        Type *type = array_type->type();
        if (auto record_type = dynamic_cast<RecordType*>(type); record_type) {
            array_type->setType(new QualidentType(new Qualident(new Identifier("RecordType" + std::to_string(record_num)))));
            go(record_type);
        }
        createVectorOfVectors(array_type->lengths()->lengths().size(), type);
    }

    void visit(BaseType *base_type) override {
        out_ << ": public ";
        go(base_type->qualident());
    }

    void visit(FieldList *field_list) override {
        addIdentTypes(field_list->identList(), field_list->type());
        go(field_list->type());
        out_ << " ";
        go(field_list->identList());
        out_ << ";\n";
    }

    void visit(FieldListSequence *field_list_sequence) override {
        for (auto& field_list : field_list_sequence->fieldLists()) {
            go(field_list);
        }
    }

    void visit(IdentDefList *ident_list) override {
        bool first = true;
        for (auto& identdef : ident_list->identdefs()) {
            if (!first) {
                out_ << ", ";
            }
            first = false;
            go(identdef);
        }
    }

    void visit(Length *length) override {
        go(length->constExpression());
    }

    void visit(LengthList *length_list) override {
        // Had to move logic in ArrayType visit
    }

    void visit(PointerType *pointer_type) override {
        if (auto record_type = dynamic_cast<RecordType*>(pointer_type->type()); record_type) {
            pointer_type->setType(new QualidentType(new Qualident(new Identifier("struct" + std::to_string(record_num)))));
            go(record_type);
        }
        go(pointer_type->type());
        out_ << "*";
    }

    void qualidentToString(Qualident *qualident) {
        std::string type = qualident->identifier()->identifier();
        if (type == "INTEGER") {
            out_ << "int";
        } else if (type == "REAL") {
            out_ << "float";
        } else if (type == "BYTE") {
            out_ << "std::byte";
        } else if (type == "BOOLEAN") {
            out_ << "bool";
        } else if (type == "CHAR") {
            out_ << "char";
        } else if (type == "SET") {
            out_ << "FactorSet";
        } else {
            go(qualident);
        }
    }

    void visit(QualidentType *qualident_type) override {
        qualidentToString(qualident_type->qualident());
    }

    void visit(RecordType *record_type) override {
        if (record_name_.empty()) {
            out_ << "struct struct" + std::to_string(record_num++);
        } else {
            out_ << "struct " + record_name_;
            record_name_.clear();
        }
        go(record_type->baseType());
        out_ << "{\n";
        go(record_type->fieldListSequence());
        out_ << "\n};\n";
    }

    void visit(TypeDeclaration *type_declaration) override {
        auto type = type_declaration->type();
        auto name = type_declaration->identDef()->identifier();
        if (auto record_type = dynamic_cast<RecordType*>(type); record_type) {
            record_name_ = name;
            type_declaration->setType(new QualidentType(new Qualident(new Identifier(name))));
            go(record_type);
            return;
        }
        if (auto pointer_type = dynamic_cast<PointerType*>(type); pointer_type) {
            is_pointer_qualident[type_declaration->identDef()->identifier()] = true;
            if (auto record_type = dynamic_cast<RecordType*>(pointer_type->type()); record_type) {
                record_name_ = name;
                auto new_type = new QualidentType(new Qualident(new Identifier(name)));
                pointer_type->setType(new_type);
                go(record_type);
            }
        }
        out_ << "using ";
        go(type_declaration->identDef());
        out_ << " = ";
        go(type_declaration->type());
        out_ << ";\n";
    }

    void visit(BinaryMinus *binary_minus) override {
        out_ << "-";
    }

    void visit(BinaryPlus *binary_plus) override {
        out_ << "+";
    }

    void visit(Division *division) override {
        out_ << "/";
    }

    void visit(IntegerDivision *integer_division) override {
        out_ << "/";
    }

    void visit(LogicalConjunction *logical_conjunction) override {
        out_ << "&&";
    }

    void visit(LogicalDisjunction *logical_disjunction) override {
        out_ << "||";
    }

    void visit(Modulo *modulo) override {
        out_ << "%";
    }

    void visit(Multiplication *multiplication) override {
        out_ << "*";
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
            out_ << " ";
            go(term->mulOperator());
            out_ << " ";
            go(term->term());
        }
    }

    void visit(TermOperation *term_operation) override {
        go(term_operation->lhs());
        if (term_operation->add_operator()) {
            out_ << ' ';
            go(term_operation->add_operator());
            out_ << ' ';
            go(term_operation->rhs());
        }
    }

    void visit(UnaryMinus *unary_minus) override {
        out_ << "-";
    }

    void visit(UnaryPlus *unary_plus) override {
        out_ << "+";
    }

    void visit(FormalParameters *formal_parameters) override {
        go(formal_parameters->fpSectionList());
    }

    void visit(FormalType *formal_type) override {
        createVectorOfVectors(formal_type->arrayDepth(), new QualidentType(formal_type->qualident()));
    }

    void visit(FPSection *fp_section) override {
        bool is_first = true;
        for (const auto& ident : fp_section->identifierList()->identifiers()) {
            if (!is_first) {
                out_ << ", ";
            }
            go(fp_section->formalType());
            if (fp_section->isVariable()) {
                out_ << "&";
            }
            out_ << " " << ident->identifier();
            variable_types[ident->identifier()] = new QualidentType(fp_section->formalType()->qualident());
            is_first = false;
        }
    }

    void visit(FPSectionList *fp_section_list) override {
        bool is_first = true;
        for (auto& fp_section : fp_section_list->FPSections()) {
            if (!is_first) {
                out_ << ", ";
            }
            is_first = false;
            go(fp_section);
        }
    }

    void visit(IdentifierList *identifier_list) override {
        // Not used
    }

    void visit(ProcedureType *procedure_type) override {
        out_ << "std::function<";
        qualidentToString(procedure_type->formal_parameters()->qualident());
        out_ << "(";
        go(procedure_type->formal_parameters());
        out_ << ")>";
    }

    void visit(VariableDeclarationList *variable_declaration_list) override {
        for (const auto& declaration : variable_declaration_list->variableDeclarations()) {
            go(declaration);
        }
    }

    void visit(ConstDeclarationList *const_declaration_list) override {
        for (const auto& declaration : const_declaration_list->constDeclarations()) {
            go(declaration);
        }
    }

    void visit(TypeDeclarationList *type_declaration_list) override {
        for (const auto& declaration : type_declaration_list->typeDeclarations()) {
            go(declaration);
        }
    }

    void visit(ProcedureDeclarationList *procedure_declaration_list) override {
        for (const auto& declaration : procedure_declaration_list->procedureDeclarations()) {
            go(declaration);
        }
    }

    void visit(DeclarationSequence *declaration_sequence) override {
        go(declaration_sequence->typeDeclarationList());
        go(declaration_sequence->constDeclarationList());
        go(declaration_sequence->variableDeclarationList());
        go(declaration_sequence->procedureDeclarationList());
    }

    void visit(Import *import) override {}

    void visit(ImportList *import_list) override {
        go(import_list->importSequence());
    }

    void visit(ImportSequence *import_sequence) override {
        if (inside_namespace_) {
            for (Import *import : import_sequence->imports()) {
                if (import->identifier()->identifier() != "In" && import->identifier()->identifier() != "Out") {
                    out_ << "using " << import->alias()->identifier() << " = __" << import->identifier()->identifier() << "__::" << import->identifier()->identifier() << "\n"; 
                }
            }
        } else {
            for (Import *import : import_sequence->imports()) {
                if (import->identifier()->identifier() != "In" && import->identifier()->identifier() != "Out") {
                    out_ << "#include \"" << import->identifier()->identifier() << ".h\"\n"; 
                }
            }
        }
    }

    void visit(NumberFactor* number_factor) override {
        go(number_factor->number());
    }

    void visit(StringFactor* string_factor) override {
        go(string_factor->string());
    }

    void visit(NilFactor* nil_factor) override {
        out_ << "NULL";
    }

    void visit(TrueFactor* true_factor) override {
        out_ << "true";
    }

    void visit(FalseFactor* false_factor) override {
        out_ << "false";
    }

    void visit(SingleElement* single_element) override {
        out_ << "Range(";
        go(single_element->expression());
        out_ << ")";
    }

    void visit(Elements* elements) override {
        go(elements->element());

        if (elements->elements()) {
            out_ << ", ";
            go(elements->elements());
        }
    }

    void visit(Range* range) override {
        out_ << "Range(";
        go(range->from());
        if (range->to()) {
            out_ << ", ";
            go(range->to());
        }
        out_ << ")";
    }

    void visit(Set* set) override {
        out_ << "FactorSet(";
        go(set->elements());
        out_ << ")";
    }

    void visit(SetFactor* set_factor) override {
        go(set_factor->set());
    }

    void visit(ExpList* exp_list) override {
        go(exp_list->expression());
        if (exp_list->expList()) {
            out_ << ", ";
            go(exp_list->expList());
        }
    }

    void visit(ActualParameters* actual_parameters) override {
        go(actual_parameters->expList());
    }

    void visit(FieldSelector *field_selector) override {
        if (use_pointer_selector) {
            out_ << "->";
        } else {
            out_ << ".";
        }
        go(field_selector->ident());
    }

    void selectArray(ExpList *list) {
        out_ << "[";
        go(list->expression());
        out_ << "]";
        if (list->expList()) {
            selectArray(list->expList());
        }
    }

    void visit(ArraySelector *array_selector) override {
        selectArray(array_selector->exp_list());
    }

    void visit(PointerDereference *pointer_dereference) override {
        out_ << "*";
    }

    void visit(Selectors *selectors) override {
        go(selectors->selector());
        go(selectors->selectors());
    }

    void visit(Designator *designator) override {
        if (isVariablePointer(designator->qualident()->identifier()->identifier())) {
            use_pointer_selector = true;
        }
        go(designator->qualident());
        go(designator->selectors());
        use_pointer_selector = false;
    }

    void visit(DesignatorFactor *designator_factor) override {
        go(designator_factor->designator());
        if (designator_factor->actualParameters()) {
            out_ << "(";
            go(designator_factor->actualParameters());
            out_ << ")";
        }
    }

    void visit(ExpressionFactor *expression_factor) override {
        out_ << "(";
        go(expression_factor->expression());
        out_ << ")";
    }

    void visit(NegationFactor *negation_factor) override {
        out_ << "!";
        go(negation_factor->factor());
    }

    void visit(EqualRelation *equal_relation) override {
        out_ << "==";
    }

    void visit(NotEqualRelation *not_equal_relation) override {
        out_ << "!=";
    }

    void visit(LessRelation *less_relation) override {
        out_ << "<";
    }

    void visit(LessEqualRelation *less_equal_relation) override {
        out_ << "<=";
    }

    void visit(GreaterRelation *greater_relation) override {
        out_ << ">";
    }

    void visit(GreaterEqualRelation *greater_equal_relation) override {
        out_ << ">=";
    }

    void visit(InRelation *in_relation) override {
        out_ << "%";
    }

    void visit(IsRelation *is_relation) override {
        out_ << "Oops";
    }

    void visit(Assignment *assignment) override {
        go(assignment->designator());
        out_ << " = ";
        go(assignment->expression());
    }

    void visit(ElsifList *elsif_list) override {
        out_ << "else if ( ";
        go(elsif_list->expression());
        out_ << ") {\n";
        go(elsif_list->statementSequence());
        out_ << "} \n";
        go(elsif_list->elsifList());
    }

    void visit(IfStatement *if_statement) override {
        out_ << "if (";
        go(if_statement->expression());
        out_ << ") {\n";
        go(if_statement->thenStatements());
        out_ << "}\n";
        go(if_statement->elsifList());
        if (if_statement->elseStatements()) {
            out_ << "else {";
            go(if_statement->elseStatements());
            out_ << "}\n";
        }
    }

    void visit(ProcedureBody *procedure_body) override {
        go(procedure_body->declarationSequence());
        go(procedure_body->body());
        if (procedure_body->returnExpression()) {
            out_ << "return ";
            go(procedure_body->returnExpression());
            out_ << ";";
        }
    }

    void visit(ProcedureCall *procedure_call) override {
        go(procedure_call->designator());
        out_ << "(";
        go(procedure_call->actualParameters());
        out_ << ")";
    }

    bool isStatementNeedsSemicolon(Statement *statement) {
        return dynamic_cast<ProcedureCall*>(statement) || dynamic_cast<Assignment*>(statement);
    }

    void visit(StatementSequence *statement_sequence) override {
        for (Statement* statement : statement_sequence->statements()) {
            go(statement);
            if (isStatementNeedsSemicolon(statement)) {
                out_ << ";\n";
            }
        }
    }

    void visit(Case *case_node) override {}
    void visit(CaseLabelList *case_label_list) override {}
    void visit(CaseList *case_list) override {}
    void visit(CaseStatement *case_statement) override {}

    void createWhileBody(Expression *condition, StatementSequence *body) {
        out_ << "if (";
        go(condition);
        out_ << ") {\n";
        go(body);
        out_ << "continue;\n";
        out_ << "}\n";
    }

    void visit(ElsifWhileList *elsif_while_list) override {
        createWhileBody(elsif_while_list->expression(), elsif_while_list->statementSequence());
        go(elsif_while_list->elsifWhileList());
    }

    void getByExpression(ConstExpression *expression) {
        if (!expression) {
            out_ << "1";
        } else {
            go(expression);
        }
    }

    void visit(ForStatement *for_statement) override {
        out_ << "for (int ";
        go(for_statement->variableName());
        out_ << " = ";
        go(for_statement->variableExpression());
        out_ << ";;";
        go(for_statement->variableName());
        out_ << " += ";
        getByExpression(for_statement->byExpression());
        out_ << ") {\n";
        out_ << "if ((";
        getByExpression(for_statement->byExpression());
        out_ << ") > 0) {\n if (";
        go(for_statement->variableName());
        out_ << " > ";
        go(for_statement->toExpression());
        out_ << ") {\n break;\n}\n} else {\n if (";
        go(for_statement->variableName());
        out_ << " < ";
        go(for_statement->toExpression());
        out_ << ") {\n break;\n}\n}\n";
        go(for_statement->body());
        out_ << "}\n";
    }

    void visit(IntegerLabel *integer_label) override {}
    void visit(LabelRange *label_range) override {}
    void visit(QualidentLabel *qualident_label) override {}

    void visit(RepeatStatement *repeat_statement) override {
        out_ << "do {\n";
        go(repeat_statement->body());
        out_ << "} while (!(";
        go(repeat_statement->expression());
        out_ << "));\n";
    }

    void visit(StringLabel *string_label) override {}

    void visit(WhileStatement *while_statement) override {
        out_ << "while (true) {\n";
        createWhileBody(while_statement->expression(), while_statement->body());
        go(while_statement->elseList());
        out_ << "break;\n";
        out_ << "}\n";
    }

private:
    bool use_pointer_selector = false;
    size_t record_num = 1;
    std::string record_name_;
    std::map<std::string, bool> is_pointer_qualident;
    std::map<std::string, Type*> variable_types;

    std::ofstream out_;
    bool inside_namespace_ = false;
};

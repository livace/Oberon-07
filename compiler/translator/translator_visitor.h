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

void createDefaultLibrary() {
    std::string library = R"a0(template <class T>
        T ABS(T x) {
            return std::abs(x);
        }

        bool ODD(int x) {
            return x & 1;
        }

        template <class T>
        int LEN(const T& array) {
            return array.size();
        }

        int LSL(int x, int n) {
            return x << n;
        }

        int RSR(int x, int n) {
            return x >> n;
        }

        int ROR(int x, int n) {
            return (x >> n) | (n << (32 - n));
        }

        int FLOOR(float x) {
            return int(std::floor(x));
        }

        float FLT(int x) {
            return float(x);
        }

        template <class T>
        int ORD(T x) {
            return static_cast<int>(x);
        }

        void INC(int& x, int n = 1) {
            x += n;
        }

        void DEC(int& x, int n = 1) {
            x -= n;
        }

        void ASSERT(bool value) {
            assert(value);
        }
        template<class T>
        void NEW(T*& x) {
            x = new(T);
        }

        class __Out__ {
        public:
            void Ln() {
                std::cout << '\n';
            }

            template<typename ... Args>
            void Int(Args ... args) {
                ((std::cout << args << ' '), ...);
            }

            template<typename ... Args>
            void Real(Args ... args) {
                ((std::cout << args << ' '), ...);
            }

            template<typename ... Args>
            void String(Args ... args) {
                ((std::cout << args << ' '), ...);
            }
        } static Out;

        class Range {
public:
    Range(int from, int to): from_(from), to_(to) {
        if (from_ > to_) {
            std::swap(from_, to_);
        }
    }

    Range(int value): from_(value), to_(value) {}

    int from() const {
        return from_;
    }

    int to() const {
        return to_;
    }
private:
    int from_, to_;
};

class FactorSet {
public:
    FactorSet() = default;

    void Add(Range range) {
        for (int i = range.from(); i <= range.to(); ++i) {
            set_.insert(i);
        }
    }

    void Add(int value) {
        set_.insert(value);
    }

    void Remove(int value) {
        set_.erase(value);
    }

    template <class T, class... Ts>
    FactorSet(T f, Ts... rest) {
        Add(f);
        *this = *this + FactorSet(rest...);
    }

    FactorSet operator + (const FactorSet& other) const {
        FactorSet temp = *this;
        temp.set_.insert(other.set_.begin(), other.set_.end());
        return temp;
    }

    FactorSet operator - (const FactorSet& other) const {
        FactorSet temp = *this;
        for (const auto& value : other.set_) {
            temp.set_.erase(value);
        }
        return temp;
    }

    FactorSet operator * (const FactorSet& other) const {
        std::set<int> result;
        for (const auto& value : set_) {
            if (other.set_.count(value)) {
                result.insert(value);
            }
        }
        return FactorSet(result);
    }

    FactorSet operator / (const FactorSet& other) const {
        std::set<int> result;
        for (const auto& value : set_) {
            if (!other.set_.count(value)) {
                result.insert(value);
            }
        }
        for (const auto& value : other.set_) {
            if (!set_.count(value)) {
                result.insert(value);
            }
        }
        return result;
    }

    bool operator == (const FactorSet& other) const {
        return other.set_ == set_;
    }

    bool operator != (const FactorSet& other) const {
        return other.set_ != set_;
    }

    void Print() const {
        for (const auto& value: set_) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }

    friend bool operator % (const FactorSet& lhs, int i);
    friend bool operator % (int i, const FactorSet& rhs);
    private:
        FactorSet(std::set<int> set) : set_(std::move(set)) {}
        std::set<int> set_;
    };

    bool operator % (const FactorSet& lhs, int i) {
        return lhs.set_.count(i);
    }

    bool operator % (int i, const FactorSet& rhs) {
        return rhs.set_.count(i);
    }

    void INCL(FactorSet& set, int value) {
        set.Add(value);
    }

    void EXCL(FactorSet& set, int value) {
        set.Remove(value);
    }
)a0";
    std::cout << library;
}

class TranslatorVisitor : public Visitor {
public:
    template <class T>
    void go(T *node) {
        if (node) {
            node->accept(*this);
        }
    }

    void visit(Identifier *identifier) override {
        std::cout << identifier->identifier();
    }

    void visit(ProcedureDeclaration *procedure_declaration) override {
        go(procedure_declaration->procedureHeading());
        std::cout << "{\n";
        go(procedure_declaration->body());
        std::cout << "}\n\n";
    }

    void getReturnType(Qualident *return_type) {
        if (return_type != nullptr) {
            qualidentToString(return_type);
        } else {
            std::cout << "void";
        }
    }

    void visit(ProcedureHeading *procedure_heading) override {
        getReturnType(procedure_heading->getProcedureReturnType());
        std::cout << " ";
        go(procedure_heading->identDef());
        std::cout << "(";
        go(procedure_heading->formalParameters());
        std::cout << " )";
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
        std::cout << " ";
        if (auto array_type = dynamic_cast<ArrayType*>(variable_declaration->type()); array_type) {
            bool is_first = true;
            for (const auto& identdef : variable_declaration->identList()->identdefs()) {
                if (!is_first) {
                    std::cout << ", ";
                }
                go(identdef);
                createVectorConstruction(array_type);
                is_first = false;
            }
        } else {
            go(variable_declaration->identList());
        }
        std::cout << ";\n";
    }

    void visit(Qualident *qualident) override {
        if (qualident->prefix()) {
            go(qualident->prefix());
            std::cerr << ".";
        }
        go(qualident->identifier());
    }

    void visit(Root *root) override {
        std::cout << "#include <bits/stdc++.h>\n";
        createDefaultLibrary();
        go(root->module());
    }

    void visit(Module *module) override {
        go(module->declarations());
        if (module->statements()) {
            std::cout << "\nint main() {\n";
            go(module->statements());
            std::cout << "}\n";
        }
    }

    void visit(ConstDeclaration *const_declaration) override {
        std::cout << "const auto ";
        go(const_declaration->identifier());
        std::cout << " = ";
        go(const_declaration->constExpression());
        std::cout << ";\n";
    }

    void visit(ConstExpression *const_expression) override {
        go(const_expression->expression());
    }

    void visit(Expression *expression) override {
        go(expression->primary());
        if (expression->relation()) {
            std::cout << " ";
            go(expression->relation());
            std::cout << " ";
            go(expression->secondary());
        }
    }

    void visit(IdentDef *identdef) override {
        std::cout << identdef->identifier();
    }

    void visit(Real *number) override {
        std::cout << number->value();
    }

    void visit(Integer *number) override {
        std::cout << number->value();
    }

    void visit(String *string) override {
        std::cout << string->value();
    }

    bool createVectorOfVectors(size_t size, Type *type) {
        if (size == 0) {
            go(type);
            return false;
        }
        if (size >= 1) {
            std::cout << "std::vector<";
            createVectorOfVectors(size - 1, type);
            std::cout << ">";
        }
        return true;
    }

    void createVectorConstruction(ArrayType *array_type) {
        std::cout << "(";
        size_t size = array_type->lengths()->lengths().size();
        Type *type = array_type->type();
        auto& lengths = array_type->lengths()->lengths();
        for (auto it = lengths.rbegin(); it != lengths.rend(); ++it) {
            go(*it);
            std::cout <<", ";
            if (size != 1) {
                if (createVectorOfVectors(--size, type)) {
                    std::cout << "(";
                }
            }
        }
        size = array_type->lengths()->lengths().size();
        std::cout << "0)";
        std::cout << std::string(size - 1, ')');
    }

    void visit(Number *number) override {
        std::cout << number->float_value();
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
        std::cout << ": public ";
        go(base_type->qualident());
    }

    void visit(FieldList *field_list) override {
        addIdentTypes(field_list->identList(), field_list->type());
        go(field_list->type());
        std::cout << " ";
        go(field_list->identList());
        std::cout << ";\n";
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
                std::cerr << ", ";
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
        std::cout << "*";
    }

    void qualidentToString(Qualident *qualident) {
        std::string type = qualident->identifier()->identifier();
        if (type == "INTEGER") {
            std::cout << "int";
        } else if (type == "REAL") {
            std::cout << "float";
        } else if (type == "BYTE") {
            std::cout << "std::byte";
        } else if (type == "BOOLEAN") {
            std::cout << "bool";
        } else if (type == "CHAR") {
            std::cout << "char";
        } else if (type == "SET") {
            std::cout << "FactorSet";
        } else {
            go(qualident);
        }
    }

    void visit(QualidentType *qualident_type) override {
        qualidentToString(qualident_type->qualident());
    }

    void visit(RecordType *record_type) override {
        if (record_name_.empty()) {
            std::cout << "struct struct" + std::to_string(record_num++);
        } else {
            std::cout << "struct " + record_name_;
            record_name_.clear();
        }
        go(record_type->baseType());
        std::cout << "{\n";
        go(record_type->fieldListSequence());
        std::cout << "\n};\n";
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
        std::cout << "using ";
        go(type_declaration->identDef());
        std::cout << " = ";
        go(type_declaration->type());
        std::cout << ";\n";
    }

    void visit(BinaryMinus *binary_minus) override {
        std::cout << "-";
    }

    void visit(BinaryPlus *binary_plus) override {
        std::cout << "+";
    }

    void visit(Division *division) override {
        std::cout << "/";
    }

    void visit(IntegerDivision *integer_division) override {
        std::cout << "/";
    }

    void visit(LogicalConjunction *logical_conjunction) override {
        std::cout << "&&";
    }

    void visit(LogicalDisjunction *logical_disjunction) override {
        std::cout << "||";
    }

    void visit(Modulo *modulo) override {
        std::cout << "%";
    }

    void visit(Multiplication *multiplication) override {
        std::cout << "*";
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
        if (term_operation->add_operator()) {
            std::cout << ' ';
            go(term_operation->add_operator());
            std::cout << ' ';
            go(term_operation->rhs());
        }
    }

    void visit(UnaryMinus *unary_minus) override {
        std::cout << "-";
    }

    void visit(UnaryPlus *unary_plus) override {
        std::cout << "+";
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
                std::cout << ", ";
            }
            go(fp_section->formalType());
            if (fp_section->isVariable()) {
                std::cout << "&";
            }
            std::cout << " " << ident->identifier();
            variable_types[ident->identifier()] = new QualidentType(fp_section->formalType()->qualident());
            is_first = false;
        }
    }

    void visit(FPSectionList *fp_section_list) override {
        bool is_first = true;
        for (auto& fp_section : fp_section_list->FPSections()) {
            if (!is_first) {
                std::cerr << ", ";
            }
            is_first = false;
            go(fp_section);
        }
    }

    void visit(IdentifierList *identifier_list) override {
        // Not used
    }

    void visit(ProcedureType *procedure_type) override {
        std::cout << "std::function<";
        qualidentToString(procedure_type->formal_parameters()->qualident());
        std::cout << "(";
        go(procedure_type->formal_parameters());
        std::cout << ")>";
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

    void visit(Import *import) override {
        // TODO: Add imports
    }

    void visit(ImportList *import_list) override {
        // TODO: Add imports
    }
    void visit(ImportSequence *import_sequence) override {
        // TODO: Add imports
    }

    void visit(NumberFactor* number_factor) override {
        go(number_factor->number());
    }

    void visit(StringFactor* string_factor) override {
        go(string_factor->string());
    }

    void visit(NilFactor* nil_factor) override {
        std::cout << "NULL";
    }

    void visit(TrueFactor* true_factor) override {
        std::cout << "true";
    }

    void visit(FalseFactor* false_factor) override {
        std::cout << "false";
    }

    void visit(SingleElement* single_element) override {
        std::cout << "Range(";
        go(single_element->expression());
        std::cout << ")";
    }

    void visit(Elements* elements) override {
        go(elements->element());

        if (elements->elements()) {
            std::cerr << ", ";
            go(elements->elements());
        }
    }

    void visit(Range* range) override {
        std::cout << "Range(";
        go(range->from());
        if (range->to()) {
            std::cout << ", ";
            go(range->to());
        }
        std::cout << ")";
    }

    void visit(Set* set) override {
        std::cout << "FactorSet(";
        go(set->elements());
        std::cout << ")";
    }

    void visit(SetFactor* set_factor) override {
        go(set_factor->set());
    }

    void visit(ExpList* exp_list) override {
        go(exp_list->expression());
        if (exp_list->expList()) {
            std::cerr << ", ";
            go(exp_list->expList());
        }
    }

    void visit(ActualParameters* actual_parameters) override {
        go(actual_parameters->expList());
    }

    void visit(FieldSelector *field_selector) override {
        if (use_pointer_selector) {
            std::cout << "->";
        } else {
            std::cout << ".";
        }
        go(field_selector->ident());
    }

    void selectArray(ExpList *list) {
        std::cout << "[";
        go(list->expression());
        std::cout << "]";
        if (list->expList()) {
            selectArray(list->expList());
        }
    }

    void visit(ArraySelector *array_selector) override {
        selectArray(array_selector->exp_list());
    }

    void visit(PointerDereference *pointer_dereference) override {
        std::cout << "*";
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
            std::cout << "(";
            go(designator_factor->actualParameters());
            std::cout << ")";
        }
    }

    void visit(ExpressionFactor *expression_factor) override {
        std::cout << "(";
        go(expression_factor->expression());
        std::cout << ")";
    }

    void visit(NegationFactor *negation_factor) override {
        std::cout << "!";
        go(negation_factor->factor());
    }

    void visit(EqualRelation *equal_relation) override {
        std::cout << "==";
    }

    void visit(NotEqualRelation *not_equal_relation) override {
        std::cout << "!=";
    }

    void visit(LessRelation *less_relation) override {
        std::cout << "<";
    }

    void visit(LessEqualRelation *less_equal_relation) override {
        std::cout << "<=";
    }

    void visit(GreaterRelation *greater_relation) override {
        std::cout << ">";
    }

    void visit(GreaterEqualRelation *greater_equal_relation) override {
        std::cout << ">=";
    }

    void visit(InRelation *in_relation) override {
        std::cout << "%";
    }

    void visit(IsRelation *is_relation) override {
        std::cout << "Oops";
    }

    void visit(Assignment *assignment) override {
        go(assignment->designator());
        std::cout << " = ";
        go(assignment->expression());
    }

    void visit(ElsifList *elsif_list) override {
        std::cout << "else if ( ";
        go(elsif_list->expression());
        std::cerr << ") {\n";
        go(elsif_list->statementSequence());
        std::cout << "} \n";
        go(elsif_list->elsifList());
    }

    void visit(IfStatement *if_statement) override {
        std::cout << "if (";
        go(if_statement->expression());
        std::cout << ") {\n";
        go(if_statement->thenStatements());
        std::cout << "}\n";
        go(if_statement->elsifList());
        if (if_statement->elseStatements()) {
            std::cout << "else {";
            go(if_statement->elseStatements());
            std::cout << "}\n";
        }
    }

    void visit(ProcedureBody *procedure_body) override {
        go(procedure_body->declarationSequence());
        go(procedure_body->body());
        if (procedure_body->returnExpression()) {
            std::cout << "return ";
            go(procedure_body->returnExpression());
            std::cout << ";";
        }
    }

    void visit(ProcedureCall *procedure_call) override {
        go(procedure_call->designator());
        std::cout << "(";
        go(procedure_call->actualParameters());
        std::cout << ")";
    }

    bool isStatementNeedsSemicolon(Statement *statement) {
        return dynamic_cast<ProcedureCall*>(statement) || dynamic_cast<Assignment*>(statement);
    }

    void visit(StatementSequence *statement_sequence) override {
        for (Statement* statement : statement_sequence->statements()) {
            go(statement);
            if (isStatementNeedsSemicolon(statement)) {
                std::cout << ";\n";
            }
        }
    }

    void visit(Case *case_node) override {}
    void visit(CaseLabelList *case_label_list) override {}
    void visit(CaseList *case_list) override {}
    void visit(CaseStatement *case_statement) override {}

    void createWhileBody(Expression *condition, StatementSequence *body) {
        std::cout << "if (";
        go(condition);
        std::cout << ") {\n";
        go(body);
        std::cout << "continue;\n";
        std::cout << "}\n";
    }

    void visit(ElsifWhileList *elsif_while_list) override {
        createWhileBody(elsif_while_list->expression(), elsif_while_list->statementSequence());
        go(elsif_while_list->elsifWhileList());
    }

    void getByExpression(ConstExpression *expression) {
        if (!expression) {
            std::cout << "1";
        } else {
            go(expression);
        }
    }

    void visit(ForStatement *for_statement) override {
        std::cout << "for (int ";
        go(for_statement->variableName());
        std::cout << " = ";
        go(for_statement->variableExpression());
        std::cout << ";;";
        go(for_statement->variableName());
        std::cout << " += ";
        getByExpression(for_statement->byExpression());
        std::cout << ") {\n";
        std::cout << "if ((";
        getByExpression(for_statement->byExpression());
        std::cout << ") > 0) {\n if (";
        go(for_statement->variableName());
        std::cout << " > ";
        go(for_statement->toExpression());
        std::cout << ") {\n break;\n}\n} else {\n if (";
        go(for_statement->variableName());
        std::cout << " < ";
        go(for_statement->toExpression());
        std::cout << ") {\n break;\n}\n}\n";
        go(for_statement->body());
        std::cout << "}\n";
    }

    void visit(IntegerLabel *integer_label) override {}
    void visit(LabelRange *label_range) override {}
    void visit(QualidentLabel *qualident_label) override {}

    void visit(RepeatStatement *repeat_statement) override {
        std::cout << "do {\n";
        go(repeat_statement->body());
        std::cout << "} while (!(";
        go(repeat_statement->expression());
        std::cout << "));\n";
    }

    void visit(StringLabel *string_label) override {}

    void visit(WhileStatement *while_statement) override {
        std::cout << "while (true) {\n";
        createWhileBody(while_statement->expression(), while_statement->body());
        go(while_statement->elseList());
        std::cout << "break;\n";
        std::cout << "}\n";
    }
private:
    bool use_pointer_selector = false;
    size_t record_num = 1;
    std::string record_name_;
    std::map<std::string, bool> is_pointer_qualident;
    std::map<std::string, Type*> variable_types;
};

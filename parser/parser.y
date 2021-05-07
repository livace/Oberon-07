%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    
    #include <parser/ast/identifier.h>
    #include <parser/ast/type.h>
    #include <parser/ast/variable_declaration.h>
    #include <parser/ast/qualident.h>
    #include <parser/ast/procedure_declaration.h>
    #include <parser/ast/procedure_heading.h>
    #include <parser/ast/module.h>
    #include <parser/ast/const_declaration.h>
    #include <parser/ast/const_expression.h>
    #include <parser/ast/expression.h>
    #include <parser/ast/identdef.h>
    #include <parser/ast/number.h>
    #include <parser/ast/string.h>
    #include <parser/ast/root.h>
    #include <parser/ast/array_type.h>
    #include <parser/ast/base_type.h>
    #include <parser/ast/field_list.h>
    #include <parser/ast/field_list_sequence.h>
    #include <parser/ast/identdef_list.h>
    #include <parser/ast/integer.h>
    #include <parser/ast/length.h>
    #include <parser/ast/length_list.h>
    #include <parser/ast/pointer_type.h>
    #include <parser/ast/qualident_type.h>
    #include <parser/ast/real.h>
    #include <parser/ast/record_type.h>
    #include <parser/ast/type_declaration.h>
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
    #include <parser/ast/formal_parameters.h>
    #include <parser/ast/formal_type.h>
    #include <parser/ast/fp_section.h>
    #include <parser/ast/fp_section_list.h>
    #include <parser/ast/identifier_list.h>
    #include <parser/ast/procedure_type.h>
    #include <parser/ast/variable_declaration_list.h>

    class Scanner;
    class Driver;
}

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    EOF 0 "end of file"
    EOL "\n"
    EQUAL "="
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    LPAREN "("
    RPAREN ")"
    LBRACE "{"
    RBRACE "}"
    SEMICOLON ";"
    COLON ":"
    POINT "."
    COMMA ","
    GREATER ">"
    GE ">="
    LESS "<"
    LE "<="
    VAR "VAR"
    RECORD "RECORD"
    POINTER "POINTER"
    SHARP "#"
    IS "IS"
    IN "IN"
    AMPERSAND "&"
    MOD "MOD"
    DIV "DIV"
    NIL "NIL"
    TRUE "TRUE"
    FALSE "FALSE"
    SET "set"
    ELSE "ELSE"
    ELSIF "ELSIF"
    THEN "THEN"
    IF "IF"
    UNTIL "UNTIL"
    REPEAT "REPEAT"
    BY "BY"
    DO "DO"
    TO "TO"
    FOR "FOR"
    PROCEDURE "PROCEDURE"
    RETURN "RETURN"
    END "END"
    BEGIN "BEGIN"
    CONST "CONST"
    TYPE "TYPE"
    OF "OF"
    ARRAY "ARRAY"
    ASSIGNMENT ":="
    LEFT_SQUARE_BRACKET "["
    RIGHT_SQUARE_BRACKET "]"
    CARET "^"
    TILDA "~"
    IMPORT "IMPORT"
    MODULE "MODULE"
    WHILE "WHILE"
;

%token <std::string> IDENT "ident"
%token <std::string> STRING "string"
%token <int> INTEGER "integer"
%token <float> REAL "real"

%nterm <Module*> module
%nterm <Root*> unit
%nterm <Identifier*> ident
%nterm <Qualident*> qualident
%nterm <ProcedureDeclaration*> ProcedureDeclaration
%nterm <ProcedureHeading*> ProcedureHeading
%nterm <IdentDef*> identdef
%nterm <Number*> number
%nterm <String*> string
%nterm <ConstExpression*> ConstExpression
%nterm <ConstDeclaration*> ConstDeclaration
%nterm <Expression*> expression
%nterm <ArrayType*> ArrayType
%nterm <BaseType*> BaseType
%nterm <FieldList*> FieldList
%nterm <FieldListSequence*> FieldListSequence
%nterm <IdentDefList*> IdentDefList
%nterm <Length*> length
%nterm <LengthList*> LengthList
%nterm <PointerType*> PointerType
%nterm <QualidentType*> QualidentType
%nterm <RecordType*> RecordType
%nterm <Type*> type
%nterm <TypeDeclaration*> TypeDeclaration
%nterm <SimpleExpression*> SimpleExpression
%nterm <MulOperator*> MulOperator
%nterm <Terms*> terms
%nterm <Term*> term 
%nterm <AddOperator*> AddOperator
%nterm <FormalParameters*> FormalParameters
%nterm <FormalType*> FormalType
%nterm <FPSection*> FPSection
%nterm <FPSectionList*> FPSectionList
%nterm <IdentifierList*> IdentifierList
%nterm <ProcedureType*> ProcedureType
%nterm <VariableDeclaration*> VariableDeclaration
%nterm <VariableDeclarationList*> VariableDeclarationList

%printer { yyo << $$; } <*>;

%%
%start unit;

unit:
    module {
    	$$ = new Root($1);
    	driver.root = $$;
    }

qualident:
    ident {$$ = new Qualident($1);}
    | ident "." ident {$$ = new Qualident($1, $3);}

identdef:
    ident {$$ = new IdentDef($1);}
    | ident "*" {$$ = new IdentDef($1, true);}

// TODO: Add to scanner?
//ScaleFactor:
//    "E" "+" INTEGER {}
//    | "E" "-" INTEGER {}

number:
    INTEGER {$$ = new Number($1);}
    | REAL {$$ = new Number($1);}

string:
    STRING {$$ = new String($1);}

ConstDeclaration:
    identdef "=" ConstExpression {$$ = new ConstDeclaration($1, $3);}

ConstExpression:
    expression {$$ = new ConstExpression($1);} // TODO: Do we really need this?

TypeDeclaration:
    identdef "=" type {$$ = new TypeDeclaration($1, $3);}

type:
    qualident {$$ = new QualidentType($1);}
    | ArrayType {$$ = $1;}
    | RecordType {$$ = $1;}
    | PointerType {$$ = $1;}
    | ProcedureType {$$ = $1;}

ArrayType:
    "ARRAY" LengthList "OF" type {$$ = new ArrayType($2, $4);}

LengthList:
    length {$$ = new LengthList($1);}
    | LengthList "," length {$1->addLength($3);}

length: // length == ConstExpression == exression
    ConstExpression {$$ = new Length($1);}

RecordType:
    "RECORD" "(" BaseType ")" FieldListSequence "END" {$$ = new RecordType($3, $5);}
    | "RECORD" FieldListSequence "END" {$$ = new RecordType($2);}
    | "RECORD" "(" BaseType ")" "END" {$$ = new RecordType($3);}
    | "RECORD" "END" {$$ = new RecordType();}

BaseType:
    qualident {$$ = new BaseType($1);}

FieldListSequence:
    FieldList {$$ = new FieldListSequence($1);}
    | FieldListSequence ";" FieldList {$1->addFieldList($3);}

FieldList:
    IdentDefList ":" type {$$ = new FieldList($1, $3);}

IdentDefList:
    identdef {$$ = new IdentDefList($1);}
    | IdentDefList "," identdef {$1->addIdentDef($3); $$ = $1;}

PointerType:
    "POINTER" "TO" type {$$ = new PointerType($3);}

ProcedureType:
    PROCEDURE {$$ = new ProcedureType(nullptr);}
    | PROCEDURE FormalParameters {$$ = new ProcedureType($2);}

VariableDeclaration:
    IdentDefList ":" type {$$ = new VariableDeclaration($1, $3);}

expression:
    SimpleExpression {$$ = new Expression();}
    | SimpleExpression relation SimpleExpression {$$ = new Expression();}

relation:
    "=" {}
    | "#" {}
    | "<" {}
    | "<=" {}
    | ">" {}
    | ">=" {}
    | "IN" {}
    | "IS" {}

SimpleExpression:
    terms { $$ = new SimpleExpression($1); }
    | "+" terms { $$ = new SimpleExpression($2, new UnaryPlus());}
    | "-" terms { $$ = new SimpleExpression($2, new UnaryMinus()); }

terms:
    term { $$ = new SingleTerm($1); }
    | term AddOperator terms { $$ = new TermOperation($1, $2, $3); }

AddOperator:
    "+" { $$ = new BinaryPlus(); }
    | "-" { $$ = new BinaryMinus(); }
    | "OR" {  $$ = new LogicalDisjunction(); }

term:
    factor { $$ = new Term(); } // TODO
    | factor MulOperator term { $$ = new Term(); } // TODO

MulOperator:
    "*" { $$ = new Multiplication(); }
    | "/" { $$ = new Division(); }
    | "DIV" { $$ = new IntegerDivision(); }
    | "MOD" { $$ = new Modulo(); }
    | "&" { $$ = new LogicalConjunction(); }

factor:
    number {}
    | string {}
    | "NIL" {}
    | "TRUE" {}
    | "FALSE" {}
    | set {}
    | designator {}
    | designator ActualParameters {}
    | "(" expression ")" {}
    | "~" factor {}

designator:
    qualident {}
    | qualident selectors {}

selectors:
    selector {}
    | selector selectors {}

set:
    "{" elements "}" {}

elements:
    element {}
    | element "," elements {}

element:
    expression {}
    | expression ".." expression

ExpList:
    expression {}
    | expression "," ExpList {}

ActualParameters:
    "(" ")" {}
    | "(" ExpList ")" {}

selector:
    "." ident {}
    | "[" ExpList "]" {}
    | "^" {}
//    | "(" qualident ")" {} // TODO: FIX

statement:
    assignment {}
    | ProcedureCall {}
    | IfStatement {}
    | CaseStatement {}
    | WhileStatement {}
    | RepeatStatement {}
    | ForStatement {}

assignment:
    designator ":=" expression {}

ProcedureCall:
    designator {}
    | designator ActualParameters {}

StatementSequence:
    | statement {}
    | statement ";" StatementSequence {}

IfStatement:
    "IF" expression "THEN" StatementSequence ElsifList "ELSE" StatementSequence "END" {}
    | "IF" expression "THEN" StatementSequence ElsifList "END" {}
    | "IF" expression "THEN" StatementSequence "ELSE" StatementSequence "END" {}
    | "IF" expression "THEN" StatementSequence "END"

ElsifList:
    "ELSIF" expression "THEN" StatementSequence {}
    | "ELSIF" expression "THEN" StatementSequence ElsifList {}

CaseStatement:
    "CASE" expression "OF" cases "END"

cases:
    case {}
    | case "|" cases {}

case:
    CaseLabelList ":" StatementSequence {}

CaseLabelList:
    LabelRange {}
    | LabelRange "," CaseLabelList {}

LabelRange:
    label {}
    | label ".." label {}

label:
    INTEGER {}
    | STRING {}
    | qualident {}

WhileStatement:
    "WHILE" expression "DO" StatementSequence "END" {}
    | "WHILE" expression "DO" StatementSequence ElsifWhileList "END" {}

ElsifWhileList:
    "ELSIF" expression "DO" StatementSequence {}
    | "ELSIF" expression "DO" StatementSequence ElsifWhileList

RepeatStatement:
    "REPEAT" StatementSequence "UNTIL" expression {}

ForStatement:
    "FOR" ident ":=" expression "TO" expression "DO" StatementSequence "END" {}
    | "FOR" ident ":=" expression "TO" expression "BY" ConstExpression "DO" StatementSequence "END" {}

ProcedureDeclaration:
    ProcedureHeading ";" ProcedureBody ident {
        $$ = new ProcedureDeclaration($1);
    }

ProcedureHeading:
    PROCEDURE identdef { $$ = new ProcedureHeading($2, nullptr); }
    | PROCEDURE identdef FormalParameters { $$ = new ProcedureHeading($2, $3); }

ProcedureBody:
    DeclarationSequence "BEGIN" StatementSequence "RETURN" expression "END" {}
    | DeclarationSequence "BEGIN" StatementSequence "END" {}
    | DeclarationSequence "RETURN" expression "END" {}
    | DeclarationSequence "END" {}

DeclarationSequence:
    | VAR VariableDeclarationList
    | "TYPE" TypeDeclarations
    | "CONST" ConstDeclarations
    | "TYPE" TypeDeclarations VAR VariableDeclarationList
    | "CONST" ConstDeclarations VAR VariableDeclarationList
    | "CONST" ConstDeclarations "TYPE" TypeDeclarations
    | "CONST" ConstDeclarations "TYPE" TypeDeclarations VAR VariableDeclarationList
    | ProcedureDeclarations
    | VAR VariableDeclarationList ProcedureDeclarations
    | "TYPE" TypeDeclarations ProcedureDeclarations
    | "CONST" ConstDeclarations ProcedureDeclarations
    | "TYPE" TypeDeclarations VAR VariableDeclarationList ProcedureDeclarations
    | "CONST" ConstDeclarations VAR VariableDeclarationList ProcedureDeclarations
    | "CONST" ConstDeclarations "TYPE" TypeDeclarations ProcedureDeclarations
    | "CONST" ConstDeclarations "TYPE" TypeDeclarations VAR VariableDeclarationList ProcedureDeclarations

ConstDeclarations:
    ConstDeclaration ";" {}
    | ConstDeclarations ConstDeclaration ";" {}

VariableDeclarationList:
    VariableDeclaration ";" {$$ = new VariableDeclarationList($1);}
    | VariableDeclarationList VariableDeclaration ";" {$1->addVariableDeclaration($2); $$ = $1;}

TypeDeclarations:
    TypeDeclaration ";" {}
    | TypeDeclarations TypeDeclaration ";" {}

ProcedureDeclarations:
    ProcedureDeclaration ";" {}
    | ProcedureDeclarations ProcedureDeclaration ";" {}

FormalParameters:
    "(" FPSectionList ")" ":" qualident {$$ = new FormalParameters($2, $5);}
    | "(" ")" ":" qualident {$$ = new FormalParameters(nullptr, $4);}
    | "(" FPSectionList ")" {$$ = new FormalParameters($2, nullptr);}
    | "(" ")" {$$ = new FormalParameters(nullptr, nullptr);}

FPSectionList:
     FPSection {$$ = new FPSectionList($1);}
     | FPSectionList ";" FPSection {$1->addFPSection($3); $$ = $1;}

FPSection:
    "VAR" IdentifierList ":" FormalType {$$ = new FPSection(true /*is_variable*/, $2, $4);}
    | IdentifierList ":" FormalType {$$ = new FPSection(false /*is_variable*/, $1, $3);}

IdentifierList:
    ident {$$ = new IdentifierList($1);}
    | IdentifierList "," ident {$1->addIdentifier($3); $$ = $1;}

FormalType:
    qualident {$$ = new FormalType($1);}
    | "ARRAY" "OF" FormalType {$3->incArrayDepth(); $$ = $3;}

module:
    "MODULE" ident ";"  ImportList DeclarationSequence "BEGIN" StatementSequence "END" ident "." {$$ = new Module();}
    | "MODULE" ident ";"  DeclarationSequence "BEGIN" StatementSequence "END" ident "." {$$ = new Module();}
    | "MODULE" ident ";"  ImportList DeclarationSequence "END" ident "." {$$ = new Module();}
    | "MODULE" ident ";"  DeclarationSequence "END" ident "." {$$ = new Module();}

ImportList:
    "IMPORT" imports ";" {}

imports:
    import {}
    | import "," imports {}

import:
    ident {}
    | ident ":=" ident {}

ident:
    "ident" {$$ = new Identifier($1);}

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

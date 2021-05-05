%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <compiler/types/identifier.h>
    #include <compiler/types/type.h>
    #include <compiler/types/variable_declaration.h>
    #include <parser/ast/procedure_declaration.h>

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

%nterm <Identifier*> ident
%nterm <ProcedureDeclaration*> ProcedureDeclaration

%printer { yyo << $$; } <*>;

%%
%start unit;

unit:
    module {std::cout << "PROGRAM";}

qualident:
    ident {}
    | ident "." ident {}

identdef:
    ident {}
    | ident "*" {}

// TODO: Add to scanner?
//ScaleFactor:
//    "E" "+" INTEGER {}
//    | "E" "-" INTEGER {}

number:
    INTEGER {std::cout << "INTEGER\n";}
    | REAL {std::cout << "REAL\n";}

string:
    STRING {std::cout << "STRING\n";}

ConstDeclaration:
    identdef "=" ConstExpression {}

ConstExpression:
    expression {}

TypeDeclaration:
    identdef "=" type

type:
    qualident {}
    | ArrayType {}
    | RecordType {}
    | PointerType {}
    | ProcedureType {}

ArrayType:
    "ARRAY" lengths "OF" type

lengths:
    length {}
    | length "," lengths {}

length:
    ConstExpression {}

RecordType:
    "RECORD" "(" BaseType ")" FieldListSequence "END" {}
    | "RECORD" FieldListSequence "END" {}
    | "RECORD" "(" BaseType ")" "END" {}
    | "RECORD" "END" {}

BaseType:
    qualident {}

FieldListSequence:
    FieldList {}
    | FieldList ";" FieldListSequence {}

FieldList:
    IdentList ":" type {}

IdentList:
    identdef {}
    | identdef "," IdentList {}

PointerType:
    "POINTER" "TO" type {}

ProcedureType:
    PROCEDURE {}
    | PROCEDURE FormalParameters {}

VariableDeclaration:
    IdentList ":" type

expression:
    SimpleExpression {std::cout << "SIMPLE EXPRESSION\n";}
    | SimpleExpression relation SimpleExpression {std::cout << "SIMPLE EXPRESSION RELATION\n";}

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
    terms {}
    | "+" terms {}
    | "-" terms {}

terms:
    term {}
    | term AddOperator terms {}

AddOperator:
    "+" {}
    | "-" {}
    | "OR" {}

term:
    factor {}
    | factor MulOperator term {}

MulOperator:
    "*" {}
    | "/" {}
    | "DIV" {}
    | "MOD" {}
    | "&" {}

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
    qualident {std::cout << "DESIGNATOR\n";}
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
        $$ = new ProcedureDeclaration();
    }

ProcedureHeading:
    PROCEDURE identdef {}
    | PROCEDURE identdef FormalParameters {}

ProcedureBody:
    DeclarationSequence "BEGIN" StatementSequence "RETURN" expression "END"
    |  DeclarationSequence "BEGIN" StatementSequence "END" {}
    | DeclarationSequence "RETURN" expression "END" {}
    | DeclarationSequence "END" {}

DeclarationSequence:
    | VAR VariableDeclarations
    | "TYPE" TypeDeclarations
    | "CONST" ConstDeclarations
    | "TYPE" TypeDeclarations VAR VariableDeclarations
    | "CONST" ConstDeclarations VAR VariableDeclarations
    | "CONST" ConstDeclarations "TYPE" TypeDeclarations
    | "CONST" ConstDeclarations "TYPE" TypeDeclarations VAR VariableDeclarations
    | ProcedureDeclarations
    | VAR VariableDeclarations ProcedureDeclarations
    | "TYPE" TypeDeclarations ProcedureDeclarations
    | "CONST" ConstDeclarations ProcedureDeclarations
    | "TYPE" TypeDeclarations VAR VariableDeclarations ProcedureDeclarations
    | "CONST" ConstDeclarations VAR VariableDeclarations ProcedureDeclarations
    | "CONST" ConstDeclarations "TYPE" TypeDeclarations ProcedureDeclarations
    | "CONST" ConstDeclarations "TYPE" TypeDeclarations VAR VariableDeclarations ProcedureDeclarations

ConstDeclarations:
    ConstDeclaration ";" {}
    | ConstDeclarations ConstDeclaration ";" {}

VariableDeclarations:
    VariableDeclaration ";" {}
    | VariableDeclarations VariableDeclaration ";" {}

TypeDeclarations:
    TypeDeclaration ";" {}
    | TypeDeclarations TypeDeclaration ";" {}

ProcedureDeclarations:
    ProcedureDeclaration ";" {}
    | ProcedureDeclarations ProcedureDeclaration ";" {}

FormalParameters:
    "(" FPSections ")" ":" qualident {}
    | "(" ")" ":" qualident {}
    | "(" FPSections ")" {}
    | "(" ")" {}

FPSections:
     FPSection {}
     | FPSection ";" FPSections {}

FPSection:
    VAR idents ":" FormalType {}
    | idents ":" FormalType {}

idents:
    ident {}
    | ident "," idents {}

FormalType:
    qualident {}
    | "ARRAY" "OF" FormalType {}

module:
    "MODULE" ident ";"  ImportList DeclarationSequence "BEGIN" StatementSequence "END" ident "." {}
    | "MODULE" ident ";"  DeclarationSequence "BEGIN" StatementSequence "END" ident "." {}
    | "MODULE" ident ";"  ImportList DeclarationSequence "END" ident "." {}
    | "MODULE" ident ";"  DeclarationSequence "END" ident "." {}

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

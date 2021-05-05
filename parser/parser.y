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
    END 0 "end of file"
    EOL "\n"
    ASSIGN "="
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
    VAR "VAR"
;

%token <std::string> IDENT "ident"
%token <std::string> STRING "string"
%token <int> INTEGER "integer"
%token <float> REAL "real"

%nterm <int> exp
%nterm <Type*> type
%nterm <Identifier*> ident
%nterm <VariableDeclaration*> variable_declaration

%printer { yyo << $$; } <*>;

%%
%start DeclarationSequence;

unit:
    variable_declaration {std::cout << "PROGRAM";}

exp:
    number {std::cout << "NUMBER\n";}
    | exp number

declaration:
    variable_declaration {}

variable_declaration:
    ident ":" type {$$ = new VariableDeclaration($1, $3);}

//type:
//    INTEGERDECLARATION {$$ = new Type($1);}

ident:
    "ident" {$$ = new Identifier($1);}

qualident:
    ident {}
    | ident "." ident {}

identdef:
    ident {}
    | ident "*" {}

ScaleFactor:
    "E" "+" INTEGER {}
    | "E" "-" INTEGER {}

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
    "PROCEDURE" {}
    | "PROCEDURE" FormalParameters {}

VariableDeclaration:
    IdentList ":" type

expression:
    SimpleExpression {}
    | relation SimpleExpression {}

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
    "+" terms {}
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
    | "set" {}
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

selector:
    "." ident {}
    | "[" ExpList "]" {}
    | "^" {}
    | "(" qualident ")"

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
    statement {}
    | statement ";" StatementSequence {}

IfStatement:
    "IF" expression "THEN" StatementSequence ElsifList "ELSE" StatementSequence "END" {}
    | "IF" expression "THEN" StatementSequence ElsifList "END" {}

ElsifList:
    "ELSIF" expression "THEN" StatementSequence {}
    | "ELSIF" expression "THEN" StatementSequence ElsifList {}

CaseStatement:
    "CASE" expression "OF" case "END"

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

// TODO: {ELSIF expression DO StatementSequence}
WhileStatement:
    "WHILE" expression "DO" StatementSequence "END" {}
    | "WHILE" expression "DO" StatementSequence ElsifList "END" {}

ElsifList:
    "ELSIF" expression "DO" StatementSequence {}
    | "ELSIF" expression "DO" StatementSequence ElsifList

RepeatStatement:
    "REPEAT" StatementSequence "UNTIL" expression {}

ForStatement:
    "FOR" ident ":=" expression "TO" expression "DO" StatementSequence "END" {}
    | "FOR" ident ":=" expression "TO" expression "BY" ConstExpression "DO" StatementSequence "END" {}

ProcedureDeclaration:
     ProcedureHeading ";" ProcedureBody ident

ProcedureHeading:
    "PROCEDURE" identdef {}
    | "PROCEDURE" identdef FormalParameters {}

ProcedureBody:
    DeclarationSequence "BEGIN" StatementSequence "RETURN" expression "END"
    |  DeclarationSequence "BEGIN" StatementSequence "END" {}
    | DeclarationSequence "RETURN" expression "END" {}
    | DeclarationSequence "END" {}

DeclarationSequence:
    ProcedureDeclarations
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

// Zero or more
ProcedureDeclarations:
    | ProcedureDeclaration ";" {}
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
    "ARRAY" "OF" qualident {}
    | "ARRAY" "OF" FormalType {}

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

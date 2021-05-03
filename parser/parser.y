%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
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
    CLASS "class"
    PUBLIC "public"
    STATIC "static"
    VOID "void"
    MAIN "main"
    SOUT "System.out.println"
    SEMICOLON ";"
    INT "int"
    BOOLEAN "boolean"
    LENGTH "length"
    POINT "."
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <int> exp

%printer { yyo << $$; } <*>;

%%
%start unit;
unit:
    main_class {};

main_class:
    "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" stmt_list "}" "}" {};

stmt_list:
    stmt stmt_list {}
    | %empty {};

stmt:
    local_var_decl {}
    | "{" stmt_list "}" {}
    | "System.out.println" "(" exp ")" ";" {std::cout << $3 << std::endl; }
    | "identifier" "=" exp ";" {driver.variables[$1] = $3; };

local_var_decl:
    var_decl {};

var_decl:
    simple_type "identifier" ";" {driver.variables[$2] = 0; }
    | array_type "identifier" ";" {driver.arrays[$2] = std::vector<int>(); };

simple_type:
    "int" {};

array_type:
    simple_type "[" "]" {};

%left "+" "-";
%left "*" "/";

exp:
    "number" {$$ = $1; }
    | "identifier" "[" exp "]" {$$ = driver.arrays[$1][$3]; }
    | "identifier" {$$ = driver.variables[$1]; }
    | exp "+" exp {$$ = $1 + $3; }
    | exp "-" exp {$$ = $1 - $3; }
    | exp "*" exp {$$ = $1 * $3; }
    | exp "/" exp {$$ = $1 / $3; }
    | "(" exp ")" {$$ = $2; }
    | "identifier" "." "length" {$$ = driver.arrays[$1].size(); };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

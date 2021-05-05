%{
    #include <climits>
    #include "driver.hh"
    #include "parser.hh"
%}

%option noyywrap nounput noinput

%option c++
%option yyclass="Scanner"

%{
  yy::parser::symbol_type make_INTEGER(
    const std::string &s,
    const yy::parser::location_type& loc
  );
  yy::parser::symbol_type make_REAL(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

ident      [a-zA-Z][a-zA-Z_0-9]*
integer    [0-9]+
real       [0-9]+.[0-9]+
string     \"(\\.|[^"\\])*\"
blank      [ \t\r]

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  yy::location& loc = driver.location;
  loc.step();
%}
IDENT
{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"RECORD"
"POINTER"
"#"
"IS"
"IN"
"&"
"MOD"
"DIV"
"NIL"
"TRUE"
"FALSE"
"set"
"ELSE"
"ELSIF"
"THEN"
"IF"
"UNTIL"
"REPEAT"
"BY"
"DO"
"TO"
"FOR"
"PROCEDURE"
"RETURN"
"END"
"BEGIN"
"CONST"
"TYPE"
"OF"
"ARRAY"
":="
"["
"]"
"^"
"~"
"VAR"      return yy::parser::make_VAR  (loc);
","        return yy::parser::make_COMMA  (loc);
"-"        return yy::parser::make_MINUS  (loc);
":"        return yy::parser::make_COLON  (loc);
"+"        return yy::parser::make_PLUS   (loc);
"*"        return yy::parser::make_STAR   (loc);
"/"        return yy::parser::make_SLASH  (loc);
"("        return yy::parser::make_LPAREN (loc);
")"        return yy::parser::make_RPAREN (loc);
"="        return yy::parser::make_ASSIGN (loc);
"."        return yy::parser::make_POINT  (loc);
"\n"       return yy::parser::make_EOL    (loc);
"{"        return yy::parser::make_LBRACE (loc);
"}"        return yy::parser::make_RBRACE (loc);
";"        return yy::parser::make_SEMICOLON (loc);

{integer}      return make_INTEGER(yytext, loc);
{real}         return make_REAL(yytext, loc);
{ident}       return yy::parser::make_IDENT(yytext, loc);
{string}       return yy::parser::make_STRING(yytext, loc);
.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_INTEGER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_INTEGER((int) n, loc);
}

yy::parser::symbol_type make_REAL(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  float n = strtof(s.c_str(), NULL);
  return yy::parser::make_REAL((float) n, loc);
}

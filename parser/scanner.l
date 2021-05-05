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
  yy::parser::symbol_type make_STRING_FROM_CHAR(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

ident      [a-zA-Z][a-zA-Z_0-9]*
integer    [0-9]+
real       [0-9]+.[0-9]+
string     \"(\\.|[^"\\])*\"
char       [0-9][0-9A-F]*X
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

{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"IMPORT"   return yy::parser::make_IMPORT (loc);
"MODULE"   return yy::parser::make_MODULE (loc);
"RECORD"   return yy::parser::make_RECORD (loc);
"POINTER"  return yy::parser::make_POINTER (loc);
"#"        return yy::parser::make_SHARP (loc);
"IS"       return yy::parser::make_IS (loc);
"IN"       return yy::parser::make_IN (loc);
"&"        return yy::parser::make_AMPERSAND (loc);
"MOD"      return yy::parser::make_MOD (loc);
"DIV"      return yy::parser::make_DIV (loc);
"NIL"      return yy::parser::make_NIL (loc);
"TRUE"     return yy::parser::make_TRUE (loc);
"FALSE"    return yy::parser::make_FALSE (loc);
"set"      return yy::parser::make_SET (loc);
"ELSE"     return yy::parser::make_ELSE (loc);
"ELSIF"    return yy::parser::make_ELSIF (loc);
"THEN"     return yy::parser::make_THEN (loc);
"WHILE"    return yy::parser::make_WHILE (loc);
"IF"       return yy::parser::make_IF (loc);
"UNTIL"    return yy::parser::make_UNTIL (loc);
"REPEAT"   return yy::parser::make_REPEAT (loc);
"BY"       return yy::parser::make_BY (loc);
"DO"       return yy::parser::make_DO (loc);
"TO"       return yy::parser::make_TO (loc);
"FOR"      return yy::parser::make_FOR (loc);
"PROCEDURE" return yy::parser::make_PROCEDURE (loc);
"RETURN"   return yy::parser::make_RETURN (loc);
"END"      return yy::parser::make_END (loc);
"BEGIN"    return yy::parser::make_BEGIN (loc);
"CONST"    return yy::parser::make_CONST (loc);
"TYPE"     return yy::parser::make_TYPE (loc);
"OF"       return yy::parser::make_OF (loc);
"ARRAY"    return yy::parser::make_ARRAY (loc);
":="       return yy::parser::make_ASSIGNMENT (loc);
"["        return yy::parser::make_LEFT_SQUARE_BRACKET (loc);
"]"        return yy::parser::make_RIGHT_SQUARE_BRACKET (loc);
"^"        return yy::parser::make_CARET  (loc);
"~"        return yy::parser::make_TILDA  (loc);
"VAR"      return yy::parser::make_VAR    (loc);
","        return yy::parser::make_COMMA  (loc);
"-"        return yy::parser::make_MINUS  (loc);
":"        return yy::parser::make_COLON  (loc);
"+"        return yy::parser::make_PLUS   (loc);
"*"        return yy::parser::make_STAR   (loc);
"/"        return yy::parser::make_SLASH  (loc);
"("        return yy::parser::make_LPAREN (loc);
")"        return yy::parser::make_RPAREN (loc);
"="        return yy::parser::make_EQUAL (loc);
"."        return yy::parser::make_POINT  (loc);
"\n"       return yy::parser::make_EOL    (loc);
"{"        return yy::parser::make_LBRACE (loc);
"}"        return yy::parser::make_RBRACE (loc);
";"        return yy::parser::make_SEMICOLON (loc);
"<"        return yy::parser::make_LESS (loc);
"<="       return yy::parser::make_LE (loc);
">"        return yy::parser::make_GREATER (loc);
">="       return yy::parser::make_GE (loc);

{integer}      return make_INTEGER(yytext, loc);
{real}         return make_REAL(yytext, loc);
{ident}        return yy::parser::make_IDENT(yytext, loc);
{string}       return yy::parser::make_STRING(yytext, loc);
{char}         return make_STRING_FROM_CHAR(yytext, loc);
.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_EOF (loc);
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
  float n = strtof(s.c_str(), NULL);
  return yy::parser::make_REAL((float) n, loc);
}

yy::parser::symbol_type make_STRING_FROM_CHAR(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  std::string temp = s.substr(0, s.size() - 1);
  std::string result(1, static_cast<char>(strtol(temp.data(), NULL, 10)));
  return yy::parser::make_STRING(result, loc);
}


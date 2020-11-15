%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::NumDriver* driver}

%code requires
{
#include <iostream>
#include <string>

// forward decl of argument to parser
namespace yy { class NumDriver; }
}

%code
{
#include "numdriver.hpp"

std::unordered_map<std::string, int> variables;

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         NumDriver* driver);
}
}

%token
  MINUS   "-"
  PLUS    "+"

  MULT    "*"
  DIV     "/"

  LBRACE   "("
  RBRACE   ")"

  EQUAL      "=="
  MORE_OR_EQ ">="
  LESS_OR_EQ "<="
  LESS       "<"
  MORE       ">"
  NOT_EQUAL  "!="
  NOT        "!"

  PRINT      "print"
  ASSIGN     "="
  INPUT      "?"

  SCOLON  ";"
  ERR
;

%token <int>  NUMBER
%token <std::string>  VARIABLE

%nterm <int>  expr
%nterm <int>  mult
%nterm <int>  term
%nterm <int>  comp
%nterm <int>  eqlist
%nterm <int>  evulate
%nterm <int>  comm


%left '+' '-' '*' '/' 

%start evulate

%%

evulate: eqlist               
;

eqlist: comm SCOLON eqlist
| comm SCOLON

comm: comp
| PRINT comp                  { std::cout << $2 << std::endl;}
| VARIABLE ASSIGN comp        {	if ($1.empty()) {std::cerr << "huy";}
variables.insert_or_assign($1, $3); std::cerr << "kek_"<< $1 << variables[$1] << "_" << std::endl;}
| VARIABLE ASSIGN INPUT       {
				int a;
				std::cin >> a;
				variables.insert_or_assign($1, a);
				std::cerr << "kek2" << $1 << std::endl;
			      }
;

comp: expr                    { $$ = $1; }
| expr EQUAL comp             { $$ = ($1 == $3); } 
| expr MORE_OR_EQ comp        { $$ = ($1 >= $3); }
| expr LESS_OR_EQ comp        { $$ = ($1 <= $3); }
| expr LESS comp              { $$ = ($1 < $3); }
| expr MORE comp              { $$ = ($1 > $3); }
| expr NOT_EQUAL comp	      { $$ = ($1 != $3); }
| NOT comp		      { $$ = (!$2); }
;


expr: mult                    { $$ = $1; }
| mult PLUS expr              { $$ = $1 + $3; }
| mult MINUS expr             { $$ = $1 - $3; }
;

mult: term                    { $$ = $1; }
| term MULT mult              { $$ = $1 * $3; }
| term DIV  mult              { $$ = $1 / $3; }
;

term: LBRACE comp RBRACE      { $$ = $2; }
| NUMBER
| VARIABLE                    {
				if (variables.count($1)) {
					std::cerr << $1 << " ERROR" << std::endl;
				}
				/*$$ = variables[$1];*/ }
;

%%

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         NumDriver* driver)
{
  return driver->yylex(yylval);
}

void parser::error(const std::string&){
  std::cerr << "Syntax ERROR" << std::endl;
}
}

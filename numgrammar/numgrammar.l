%option c++

%{

#include "numgrammar.tab.hh"

%}

WS      [ \t\n\v]+
DIGIT   [0-9]
DIGIT1  [1-9]
WORD_BEGIN  [a-zA-Z]
WORD        [a-zA-Z0-9]

%%

{WS}              /* skip blanks and tabs */

"+"               return yy::parser::token_type::PLUS;
"-"               return yy::parser::token_type::MINUS;
"*" 			  return yy::parser::token_type::MULT;
"/" 			  return yy::parser::token_type::DIV;

"(" 			  return yy::parser::token_type::LBRACE;
")"     		  return yy::parser::token_type::RBRACE;

"=="              return yy::parser::token_type::EQUAL;
">=" 			  return yy::parser::token_type::MORE_OR_EQ;
"<="		      return yy::parser::token_type::LESS_OR_EQ;
"<" 			  return yy::parser::token_type::LESS;
">"		     	  return yy::parser::token_type::MORE;
"!="              return yy::parser::token_type::NOT_EQUAL;
"!"               return yy::parser::token_type::NOT;

"=" 			  return yy::parser::token_type::ASSIGN;
"?" 			  return yy::parser::token_type::INPUT;
"print" 		  return yy::parser::token_type::PRINT;

";"               return yy::parser::token_type::SCOLON;

{DIGIT1}{DIGIT}*            return yy::parser::token_type::NUMBER;
[a-zA-Z][a-zA-Z0-9]*        return yy::parser::token_type::VARIABLE;
.			                return yy::parser::token_type::ERR;

%%

// nothing
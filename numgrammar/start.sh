flex numgrammar.l
bison numgrammar.y
g++ numgrammar.tab.cc lex.yy.cc driver.cc numdriver.hpp -o puk -std=c++1z
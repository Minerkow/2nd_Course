#include "../Parser.h"
#include "../Lexer.h"
#include <gtest/gtest.h>

TEST(Parser, Syntax_Tree) {
    std::string code1 = "a = 5;";
    parser::Parser_t pars1{code1};
    std::stringstream str1;
    pars1.Print_Syntax_Tree(str1);
    std::string res1 = "SENTENCE #0 ASSIGN SENTENCE #1 ASSIGN VAR: a NUM: 5 ";
    ASSERT_EQ(res1, str1.str());

    std::string code2 = "if (a != 7) { b = 5;}";
    parser::Parser_t pars2{code2};
    std::stringstream str2;
    pars2.Print_Syntax_Tree(str2);
    std::string res2 = "SENTENCE #0 IF SENTENCE #1 IF NOT_EQUAL SENTENCE #0 NOT_EQUAL VAR: a NUM: 7 SENTENCE #0 ASSIGN SENTENCE #1 ASSIGN VAR: b NUM: 5 ";
    ASSERT_EQ(res2, str2.str());

    std::string code3 = "a = ((b - 8) + (c * 23));";
    parser::Parser_t pars3{code3};
    std::stringstream str3;
    std::string res3 = "SENTENCE #0 ASSIGN SENTENCE #1 ASSIGN VAR: a ADD ADD SUB MUL SUB VAR: b NUM: 8 MUL VAR: c NUM: 23 ";
    pars3.Print_Syntax_Tree(str3);
    ASSERT_EQ(res3, str3.str());
}

TEST(Parser, Evulate) {
    std::string code1 = "a = 5 * 7; print a;";
    parser::Parser_t pars1{code1};
    pars1.Run();
}

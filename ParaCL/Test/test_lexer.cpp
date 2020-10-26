#include "../Lexer.h"
#include <gtest/gtest.h>

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


TEST(Lexer, compar_signs) {
    std::string code1{"== >= <= ! !="};
    lexer::LexArray_t lexer1{code1};
    std::string res1 = "EQUAL EQ_OR_GR EQ_OR_LESS NOT NOT_EQUAL ";
    std::ostringstream str1;
    str1 << lexer1;
    ASSERT_EQ(str1.str(), res1);

    std::string code2{"print if while ? = ;"};
    lexer::LexArray_t lexer2{code2};
    std::string res2 = "PRINT IF WHILE INPUT ASSIGN END_COMMAND ";
    std::ostringstream str2;
    str2 << lexer2;
    ASSERT_EQ(str2.str(), res2);

    std::string code3{"dncsjn f123 25 lmc kkccz"};
    lexer::LexArray_t lexer3{code3};
    std::string res3 = "VAR: dncsjn VAR: f123 NUM: 25 VAR: lmc VAR: kkccz ";
    std::ostringstream str3;
    str3 << lexer3;
    ASSERT_EQ(str3.str(), res3);

    std::string code4{"a = 5;"};
    lexer::LexArray_t lexer4{code4};
    std::string res4 = "VAR: a ASSIGN NUM: 5 END_COMMAND ";
    std::ostringstream str4;
    str4 << lexer4;
    ASSERT_EQ(res4, str4.str());

    std::string code5 = "{ b = 5;}";
    lexer::LexArray_t lexer5(code5);
    std::string res5{"LFIGURBRAC VAR: b ASSIGN NUM: 5 END_COMMAND RFIGURBRAC "};
    std::ostringstream str5;
    str5 << lexer5;
    ASSERT_EQ(str5.str(), res5);
}
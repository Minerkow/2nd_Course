#include "../Lexer.h"
#include <gtest/gtest.h>

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


TEST(Lexer, compar_signs) {
    std::string code1{"== >= <= ! !="};
    lexer::Lexer_t lexer1{code1};
    std::string res1 = "EQUAL EQ_OR_GR EQ_OR_LESS NOT NOT_EQUAL ";
    std::ostringstream str1;
    str1 << lexer1;
    ASSERT_EQ(str1.str(), res1);

    std::string code2{"print if while ? = ;"};
    lexer::Lexer_t lexer2{code2};
    std::string res2 = "PRINT IF WHILE INPUT ASSIGN END_COMMAND ";
    std::ostringstream str2;
    str2 << lexer2;
    ASSERT_EQ(str2.str(), res2);

    std::string code3{"dncsjn f123 25 lmc kkccz"};
    lexer::Lexer_t lexer3{code3};
    std::string res3 = "VAR: dncsjn VAR: f123 NUM: 25 VAR: lmc VAR: kkccz ";
    std::ostringstream str3;
    str3 << lexer3;
    ASSERT_EQ(str3.str(), res3);
}
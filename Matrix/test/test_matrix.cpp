#include "../Matrix.hpp"
#include <gtest/gtest.h>

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(Matrix, operator_mult) {
    mtrx::Matrix_t<double>  matrix{{ {1.1, 1.1, 1.1},
                                     {1.1, 1.1, 1.1},
                                     {1.1, 1.1, 1.1} }};
    mtrx::Matrix_t<double> res{{ {2.2, 2.2, 2.2},
                                 {2.2, 2.2, 2.2},
                                 {2.2, 2.2, 2.2} }};
    mtrx::Matrix_t<double> m = 2*matrix;

    ASSERT_EQ(2*matrix, res);
    ASSERT_EQ(matrix*2, res);
}

TEST(Matrix, operator_plus) {
    mtrx::Matrix_t<double>  matrix1 {{ {1.1, 1.1, 1.1},
                                       {1.1, 1.1, 1.1},
                                       {1.1, 1.1, 1.1} }};
    mtrx::Matrix_t<double> matrix2 {{ {2.2, 2.2, 2.2},
                                      {2.2, 2.2, 2.2},
                                      {2.2, 2.2, 2.2} }};
    mtrx::Matrix_t<double> res {{ {3.3, 3.3, 3.3},
                                  {3.3, 3.3, 3.3},
                                  {3.3, 3.3, 3.3}}};

}

TEST(Matrix, Transposition) {
    mtrx::Matrix_t<int> matrix{{{1, 2, 3, 4},
                                {5, 6, 7, 8},
                                {9, 10, 11, 12}}};
    mtrx::Matrix_t<int> res{{{1, 5, 9},
                             {2, 6, 10},
                             {3, 7, 11},
                             {4, 8, 12}}};
    mtrx::Matrix_t<int> m = matrix.Transposition();
    std::cout << m;
    ASSERT_EQ(matrix.Transposition(), res);
}
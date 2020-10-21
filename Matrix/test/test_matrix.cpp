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
    ASSERT_EQ(res, matrix1 + matrix2);

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
    ASSERT_EQ(matrix.Transposition(), res);
}

TEST(Matrix, Matrix_Mult) {
    mtrx::Matrix_t<int> matrix1{{{1, 2, 3, 4},
                                 {5, 6, 7, 8},
                                 {9, 10, 11, 12}}};
    mtrx::Matrix_t<int> matrix2{{{1, 2, 3},
                                 {4, 5, 6},
                                 {7, 8, 9},
                                 {10, 11, 12}}};
    //std::cout << matrix1 << matrix2;
    mtrx::Matrix_t<int> trueRes {{{70, 80, 90},
                              {158, 184, 210},
                              {246, 288, 330}}};
    mtrx::Matrix_t<int> res = matrix1.Matrix_Mult(matrix2);
    //std::cout << res;
    ASSERT_EQ(res, trueRes);
}

TEST(Matrix, Operators) {
    mtrx::Matrix_t<double>  matrix1 {{ {1.1, 1.1, 1.1},
                                       {1.1, 1.1, 1.1},
                                       {1.1, 1.1, 1.1} }};
    mtrx::Matrix_t<double> matrix2 {{ {2.2, 2.2, 2.2},
                                      {2.2, 2.2, 2.2},
                                      {2.2, 2.2, 2.2} }};
    mtrx::Matrix_t<double> matrix3 {{ {3.3, 3.3, 3.3},
                                      {3.3, 3.3, 3.3},
                                      {3.3, 3.3, 3.3}}};
    matrix1 += matrix1;

    ASSERT_EQ(matrix1, matrix2);

    matrix2 *= 1.5;

    ASSERT_EQ(matrix2, matrix3);
}

TEST(Matrix, Operator_SqBrace) {
    mtrx::Matrix_t<double>  matrix {{ {1.1, 1.1, 1.1},
                                       {1.1, 1.1, 1.1},
                                       {1.1, 1.1, 1.1} }};
    ASSERT_NEAR(1.1, matrix[1][1], mtrx::PRESISION);
}

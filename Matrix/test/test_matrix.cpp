#include "../Matrix.hpp"
#include "test_generator.hpp"
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

TEST(Matrix, Constructor) {
    mtrx::Matrix_t<int> matrix{{{1, 2, 3, 4},
                                {5, 6, 7, 8},
                                {9, 10, 11, 12}}};
    mtrx::Matrix_t<double> matrix1{matrix};
    mtrx::Matrix_t<double> res{{{1.0, 2.0, 3.0, 4.0},
                                {5.0, 6.0, 7.0, 8.0},
                                {9.0, 10.0, 11.0, 12.0}}};
    ASSERT_EQ(matrix1, res);
}

TEST(Matrix, Determinant1) {
    mtrx::Matrix_t<int> matrix{{{1, 2, 3, 4, 5},
                                       {6, 7, 8, 9, 10},
                                       {11, 12, 13, 14, 15},
                                       {16, 17, 18, 19, 20},
                                       {21, 22, 23, 24, 25}}};

    ASSERT_NEAR(matrix.Determinant(), 0, mtrx::PRESISION);
}

TEST(Matrix, Determinant2) {
    mtrx::Matrix_t<int> matrix1{{{1, 2},
                                 {3, 4}}};

    ASSERT_NEAR(matrix1.Determinant(), -2, mtrx::PRESISION);
}

TEST(Matrix, Determinant3) {
        mtrx::Matrix_t<int> matrix2{{{1, 2, 3},
                                     {4, -2, 6},
                                     {7, 8, 9}}};

        ASSERT_NEAR(matrix2.Determinant(), 84, mtrx::PRESISION);
}

TEST(Matrix, Determinant4) {
    mtrx::Matrix_t<double> matrix3{{{1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1},
                                    {1.1, 2, 1.1, 1.1, 1.1, 1.1, 1.1},
                                    {1.1, 1.1, 3, 1.1, 1.1, 1.1, 1.1},
                                    {1.1, 1.1, 1.1, 4, 1.1, 1.1, 1.1},
                                    {1.1, 1.1, 1.1, 1.1, 5, 1.1, 1.1},
                                    {1.1, 1.1, 1.1, 1.1, 1.1, 6, 1.1},
                                    {1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 7}}};

    ASSERT_NEAR(matrix3.Determinant(), 398.46064, mtrx::PRESISION);
}

TEST(Matrix, Determinant5) {
    mtrx::Matrix_t<int> matrix{{{0, 0, 0, -1},
                                {0, 0, -1, 0},
                                {0, 1, 0, 0},
                                {1, 0, 0, 0}}};
    ASSERT_NEAR(matrix.Determinant(), 1, mtrx::PRESISION);
}

TEST(Matrix, Determinant6) {
    mtrx::Matrix_t<int> matrix{{{84, 75, 42, 19, 1},
                                {52, 101, 78, 70, 7},
                                {18, 68, 49, 36, 3},
                                {17, 61, 59, 73, 8},
                                {2, 7, 7, 9, 1}}};
    ASSERT_NEAR(matrix.Determinant(), 1, mtrx::PRESISION);
}

TEST(Matrix, Determinant7) {
    mtrx::Matrix_t<int> matrix{{{0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0}}};
    ASSERT_NEAR(matrix.Determinant(), 0, mtrx::PRESISION);
}

TEST(Matrix, Add_Row) {
    mtrx::Matrix_t<int> matrix{{{0, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 0}}};
    mtrx::Matrix_t<int> res{{{0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0},
                             {1, 1, 1, 1, 1}}};
    mtrx::Matrix_t<int> row{{{1, 1, 1, 1, 1}}};

    matrix.Add_Row(row);

    ASSERT_EQ(res, matrix);
}

TEST(Matrix, Without_Row) {
    mtrx::Matrix_t<int> res{{{0, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 0}}};
    mtrx::Matrix_t<int> matrix{{{0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0},
                                    {1, 1, 1, 1, 1}}};

    mtrx::Matrix_t<int> m = matrix.Without_Row(5);

    ASSERT_EQ(res, m);
}

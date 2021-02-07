#include "../Graph.hpp"
#include <gtest/gtest.h>

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(Graph, GaussTest1) {
    mtrx::Matrix_t<double> mtrx1 {{ {3, 2, -5, -1},
                                    {2, -1, 3, 13},
                                    {1, 2, -1, 9} }};
    std::vector<double> res =
            grph::Gaussian_Method(mtrx1);
    ASSERT_TRUE(mtrx::Double_Equal(res[0], 3) &&
                mtrx::Double_Equal(res[1], 5) &&
                mtrx::Double_Equal(res[2], 4));
}

TEST(Graph, GaussTest2) {
    mtrx::Matrix_t<double> mtrx1 {{ {4, 2, -1, 1},
                                    {5, 3, -2, 2},
                                    {3, 2, -3, 0} }};
    std::vector<double> res = grph::Gaussian_Method(mtrx1);
    ASSERT_TRUE(mtrx::Double_Equal(res[0], -1) &&
                mtrx::Double_Equal(res[1], 3) &&
                mtrx::Double_Equal(res[2], 1));
}

TEST(Graph, Find_Potential1) {
    std::string str = "1 -- 2, 1.0; 1.0V\n"
                     "2 -- 1, 1.0;";
    std::stringstream is{str};
    grph::RTGraph_t rtGraph{is};
    std::vector<double> res = rtGraph.Calculate_Potential();
    ASSERT_TRUE(mtrx::Double_Equal(res[0], -0.5));
}


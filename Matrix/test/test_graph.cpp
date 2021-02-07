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
    std::cout << std::endl;
    for (auto& it : res) {
        std::cout << it << " ";
    }
}

TEST(Graph, GaussTest2) {
    mtrx::Matrix_t<double> mtrx1 {{ {4, 2, -1, 1},
                                    {5, 3, -2, 2},
                                    {3, 2, -3, 0} }};
    std::vector<double> res = grph::Gaussian_Method(mtrx1);
    std::cout << std::endl;
    for (auto& it : res) {
        std::cout << it << " ";
    }
}
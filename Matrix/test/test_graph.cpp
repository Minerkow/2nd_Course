#include "../Graph.hpp"
#include <gtest/gtest.h>
#include <fstream>

#define PATH __FILE__

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

TEST(Graph, Find_Amperage1) {
    std::string pathIn {PATH};
    std::string pathOut {PATH};
    pathIn = pathIn.substr(0, pathIn.size() - 14) + "FileTestForGraph/test1.in";
    pathOut = pathOut.substr(0, pathOut.size() - 14) + "FileTestForGraph/test1.out";
    std::ifstream is{pathIn};
    std::ifstream out{pathOut};

    grph::RTGraph_t rtGraph{is};
    std::stringstream res;
    rtGraph.Calculate_Print_Amperage(res);
    std::string trueRes(res.str().size(), 0);
    out.read(const_cast<char *>(trueRes.c_str()), trueRes.size());

    ASSERT_EQ(res.str(), trueRes);
}

TEST(Graph, Find_Amperage2) {
    std::string pathIn {PATH};
    std::string pathOut {PATH};
    pathIn = pathIn.substr(0, pathIn.size() - 14) + "FileTestForGraph/test2.in";
    pathOut = pathOut.substr(0, pathOut.size() - 14) + "FileTestForGraph/test2.out";
    std::ifstream is{pathIn};
    std::ifstream out{pathOut};

    grph::RTGraph_t rtGraph{is};
    std::stringstream res;
    rtGraph.Calculate_Print_Amperage(res);
    std::string trueRes(res.str().size(), 0);
    out.read(const_cast<char *>(trueRes.c_str()), trueRes.size());
    std::cout << res.str();
    //ASSERT_EQ(res.str(), trueRes);
}


TEST(Graph, Find_Amperage3) {
    std::string pathIn {PATH};
    std::string pathOut {PATH};
    pathIn = pathIn.substr(0, pathIn.size() - 14) + "FileTestForGraph/test3.in";
    pathOut = pathOut.substr(0, pathOut.size() - 14) + "FileTestForGraph/test3.out";
    std::ifstream is{pathIn};
    std::ifstream out{pathOut};

    grph::RTGraph_t rtGraph{is};
    std::stringstream res;
    rtGraph.Calculate_Print_Amperage(res);
    std::string trueRes(res.str().size(), 0);
    out.read(const_cast<char *>(trueRes.c_str()), trueRes.size());
    std::cout << res.str();

    //ASSERT_EQ(res.str(), trueRes);
}


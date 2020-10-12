#include <gtest/gtest.h>
#include "../Triangle.h"
#include "../IntersectionTriangles.h"
#include "test_generator.h"


TEST(TrianglesGenerator, Constructor) {
    trgtest::TrianglesGenerator_t test;
    //std::cout << test;
    int start_time = clock();
    std::unordered_set<size_t> res;
    std::vector<trs::triangleIterator> data;
    for (auto& it : test.triangles_) {
        data.emplace_back(&it);
    }
    trs::Triangles_IntersectionN2(data, res);
    int midl_time = clock();
    std::cout << "\n";
    for (auto& it : res) {
        std::cout << it << " ";
    }
    std::cout << "\n";
    trs::Triangles_t trs{test.triangles_};
    trs.Output_Intersecting_Triangles();
    std::unordered_set<size_t> res2 = trs.Intersecting_Triangles();
    int end_time = clock();

    std::cout << "\n" << midl_time - start_time << " " << end_time - midl_time;
    ASSERT_TRUE(res == res2);
}
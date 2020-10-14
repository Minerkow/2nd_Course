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

    std::cout << "Time N^2:" << midl_time - start_time << " Time Octree:" << end_time - midl_time;
   // ASSERT_TRUE(res == res2);
}

TEST(Cube, Is_Cube_Triangle) {
    gmtr::Triangle_t tr1{{0, 0, 0}, {1, 1, 1}, {1, 0, 0}};
    gmtr::Triangle_t tr2{{-1, -1, -1}, {1, 1, 1}, {1, 0, 0}};
    gmtr::Triangle_t tr3{{-100, -100, -100}, {100, 100, 100}, {100, 0, 0}};

    trs::Cube_t cube{{-2, -2, -2}, 4};


    ASSERT_TRUE(cube.Is_Cube_Triangle(tr1));
    ASSERT_TRUE(cube.Is_Cube_Triangle(tr2));
    ASSERT_FALSE(cube.Is_Cube_Triangle(tr3));
}
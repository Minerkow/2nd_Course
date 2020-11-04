#include <gtest/gtest.h>
#include <fstream>
#include "../Triangle.h"
#include "../IntersectionTriangles.h"
#include "test_generator.h"


TEST(TrianglesGenerator, Constructor) {
    for (int i = 0; i < 0; ++i) {
        trgtest::TrianglesGenerator_t test;
        std::unordered_set<size_t> res;
        std::vector<trs::triangleIterator> data;
        for (auto &it : test.triangles_) {
            data.emplace_back(&it);
        }
        std::set<size_t> resSet;
        trs::Triangles_IntersectionN2(data, res);
        for (auto &it : res) {
            resSet.emplace(it);
        }
        trs::Triangles_t trs{test.triangles_};
        //std::unordered_set<size_t> res2 = trs.Intersecting_Triangles();
        //trs.Output_Intersecting_Triangles();
        //if (!trs::Unordered_Set_Equal(res2, res)) {
            std::cout << "\n";
            std::cout << test;
            for (auto &it : resSet) {
                std::cout << it << " ";
            }
            std::cout << std::endl;
            trs.Output_Intersecting_Triangles();
            return;
        //}
    }
    //std::cout << std::endl << "Time N^2:" << midl_time - start_time << " Time Octree:" << end_time - midl_time;
    //ASSERT_TRUE(trs::Unordered_Set_Equal(res2, res));
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

TEST(Triangle, Triangle_Intersections1) {
    std::vector<gmtr::Triangle_t> trgs;
    trgs.push_back({{0, 0, 0},
                    {1, 0, 0},
                    {0, 1, 0}});
    trgs.push_back({{5, 5, 5},
                    {5, 5, 5},
                    {5, 5, 5}});
    trgs.push_back({{0,  0.5, -0.5},
                    {0,  0,   0.5},
                    {-1, 0,   0}});

    trs::Triangles_t trs{trgs};
    std::unordered_set<size_t> res = trs.Intersecting_Triangles();
    ASSERT_TRUE(res.empty());
}
TEST(Triangle, Triangle_Intersections2) {

    std::vector<gmtr::Triangle_t> trgs1;
    trgs1.push_back({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, 0});
    trgs1.push_back({{5, 5, 5}, {0, 0, 0}, {5, 0, 0}, 1});

    trs::Triangles_t trs1{trgs1};

    std::unordered_set<size_t> res1 = trs1.Intersecting_Triangles();
    std::unordered_set<size_t> trueRes1;
    trueRes1.emplace(0);
    trueRes1.emplace(1);
    ASSERT_TRUE(trs::Unordered_Set_Equal(res1, trueRes1));
}
    //CHECK IN GEOGEBRA
TEST(Triangle, Triangle_Intersections3) {

    std::vector<gmtr::Triangle_t> trgs3;
    trgs3.push_back(
            {{-1.0914, 0.324276, 0.730663}, {-1.06508, -1.00475, -2.04093}, {-0.585957, -0.763759, -2.03131}, 0});
    trgs3.push_back(
            {{0.193952, 0.427089, 1.16151}, {-0.102549, 1.25552, -0.258662}, {-0.0019806, 0.597291, 1.11956}, 1});
    trgs3.push_back(
            {{0.0619925, -1.37186, 0.432083}, {-0.117892, -1.1863, 0.528783}, {0.264464, -0.580351, 0.636569}, 2});
    trgs3.push_back(
            {{-0.160506, 0.136387, -0.797714}, {0.438334, 0.736186, 2.69238}, {-1.20032, 0.071876, 1.43957}, 3});
    trgs3.push_back(
            {{0.797585, -0.732483, 0.0479923}, {1.09672, -0.81792, -0.088457}, {1.08979, -0.800348, -0.119569}, 4});

    trs::Triangles_t trs3{trgs3};
    std::unordered_set<size_t> res3 = trs3.Intersecting_Triangles();
    std::unordered_set<size_t> trueRes3;
    trueRes3.emplace(3);
    trueRes3.emplace(1);
    ASSERT_TRUE(trs::Unordered_Set_Equal(res3, trueRes3));
}

TEST(Triangle, Triangle_Intersections4) {

    std::vector<gmtr::Triangle_t> trgs4;
    trgs4.push_back({{0, 0, 0}, {1, 1, 1}, {1, 1, 0}, 0});
    trgs4.push_back({{0, 0, 0}, {1, 0, 0}, {0, 0, 1}, 1});
    trgs4.push_back({{0.5, -0.5, 0}, {0.5, 0.5, 0}, {0.5, 0, 1}, 2});
    trgs4.push_back({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}, 3});

    trs::Triangles_t trs4{trgs4};
    std::unordered_set<size_t> res4 = trs4.Intersecting_Triangles();
    std::unordered_set<size_t> trueRes4;
    trueRes4.emplace(2);
    trueRes4.emplace(1);
    trueRes4.emplace(0);
    ASSERT_TRUE(trs::Unordered_Set_Equal(res4, trueRes4));
}

TEST(Triangle, Triangle_Intersections5) {
    std::vector<gmtr::Triangle_t> trgs;
    trgs.push_back({{ 1, 1, 0}, {3, 1, 0}, {1, 3, 0}, 0});
    trgs.push_back({{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, 1});
    trgs.push_back({{ 1, 0.5, 0}, {1, 0.5, 1}, {0, 0, 0.5}, 2});
    trgs.push_back({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, 3});
    trgs.push_back({{0, 0, 0}, {0, 3, 3}, {0, 0, 3}, 4});
    trgs.push_back({{1, 1, 0}, {1, 2 , 3}, { 5, 4, 8}, 5});
    trgs.push_back({{9, 9, 9}, {9, 9, 9}, {9, 9, 9}, 6});
    trgs.push_back({{8, 8, 8}, {8, 8, 8}, {-10, 8, 8}});

    trs::Triangles_t trs{trgs};
    std::unordered_set<size_t> trueRes;
    trueRes.emplace(0);
    trueRes.emplace(1);
    trueRes.emplace(2);
    trueRes.emplace(3);
    trueRes.emplace(4);
    trueRes.emplace(5);
    std::unordered_set<size_t> res = trs.Intersecting_Triangles();
    ASSERT_TRUE(trs::Unordered_Set_Equal(res, trueRes));
}

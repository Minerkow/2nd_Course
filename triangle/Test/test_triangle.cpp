#include "../Triangle.h"
#include <gtest/gtest.h>


TEST(Vector, Vector_Mult) {
    gmtr::Vector_t v1 {1, 1.5, 5.7};
    gmtr::Vector_t v2 {1, 1, 1};
    gmtr::Vector_t res {-4.2, 4.7, -0.5};

    ASSERT_EQ(v1.Vector_Mult(v2), res);

    gmtr::Vector_t v3 {1, 0, 3};
    gmtr::Vector_t v4 {2, 3, 3};
    gmtr::Vector_t res2 {-9, 3, 3};

    ASSERT_EQ(res2, v3.Vector_Mult(v4));
}

TEST(Vector, Scalar_Mult) {
    gmtr::Vector_t v1 {1, 1.5, 5.7};
    gmtr::Vector_t v2 {1, 1, 1};
    double res = 8.2;

    ASSERT_EQ(v1.Scalar_Mult(v2), res);
}

TEST(Plane, Planes_Intersection) {
    gmtr::Plane_t plane1{1, 0, 3, 7};
    gmtr::Plane_t plane2{2, 3, 3, 2};
    gmtr::Line_t resLine{{double {2} / double {3}, -1, 3},
                         {-9, 3, 3}};

    ASSERT_TRUE(resLine.point() == plane1.Planes_Intersection(plane2).point());
    ASSERT_TRUE(resLine.vector() == plane1.Planes_Intersection(plane2).vector());
    ASSERT_TRUE(plane1.Planes_Intersection(plane2).IsValid());

    gmtr::Plane_t plane3{1, 0, 3, 7};

    ASSERT_FALSE(plane1.Planes_Intersection(plane3).IsValid());
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
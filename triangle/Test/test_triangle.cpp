#include "../Triangle.h"
#include <gtest/gtest.h>

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

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
    gmtr::Line_t resLine{gmtr::Point_t{double {2} / double {3}, -1, 3},
                         gmtr::Vector_t{-9, 3, 3}};

    ASSERT_TRUE(resLine.point() == plane1.Planes_Intersection(plane2).point());
    ASSERT_TRUE(resLine.vector() == plane1.Planes_Intersection(plane2).vector());
    ASSERT_TRUE(plane1.Planes_Intersection(plane2).IsValid());

    gmtr::Plane_t plane3{1, 0, 3, 7};

    ASSERT_FALSE(plane1.Planes_Intersection(plane3).IsValid());
}

TEST(Point, Distance_to_Point) {
    gmtr::Point_t p1{1, 7, 9.6};
    gmtr::Point_t p2{-3, -2.4, 1};

    ASSERT_TRUE(std::abs(p1.Distance_to_Point(p2) - 13.353651) < gmtr::PRESISION);
}

TEST(Point, Distance_to_Plane) {
    gmtr::Point_t p{0, 3, 6};
    gmtr::Plane_t pln{2, 4, -4, -6};
    ASSERT_TRUE(p.Distince_to_Plane(pln) + 3 < gmtr::PRESISION);
}

TEST(Line, Intersection_with_Line) {
    gmtr::Line_t line1{gmtr::Point_t{ 3, -3, 2},
                       gmtr::Vector_t{-1, 1, 2}};
    gmtr::Line_t line2{gmtr::Point_t{ -1, 4, -26},
                       gmtr::Vector_t{3, -4, 6}};
    gmtr::Point_t point{8, -8, -8};

    gmtr::Point_t res = line1.Intersection_with_Line(line2);

    ASSERT_EQ(point, res);

    gmtr::Line_t line3{gmtr::Point_t{ 0, 0, 0},
                       gmtr::Vector_t{1, 1, 0}};
    gmtr::Line_t line4{gmtr::Point_t{ 1, 1, 1},
                       gmtr::Vector_t{0, 0, 1}};

    gmtr::Point_t point1{1, 1, 0};

    gmtr::Point_t res1 = line3.Intersection_with_Line(line4);
    ASSERT_EQ(point1, res1);

}


TEST(Interval, is_Interval_Point) {
    gmtr::Point_t point{1, 1, 1};
    gmtr::Interval_t interval{{2, 2, 2}, {-3, -3, -3}};

    ASSERT_TRUE(interval.is_Interval_Point(point));
}

TEST(Interval, Intersection_with_Interval) {
    gmtr::Interval_t i1{{0, -1, 0}, {0, 1, 0}};
    gmtr::Interval_t i2{{-1, 0, 0}, {1, 0, 0}};

    ASSERT_TRUE(i1.Intersection_with_Interval(i2));

    gmtr::Interval_t i3{{1, 0, 0}, {0, 0 , 0}};
    gmtr::Interval_t i4{{1, 0, 0}, {2, 0, 0}};

    ASSERT_TRUE(i1.Intersection_with_Interval(i2));
}




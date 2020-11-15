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
    gmtr::Triangle_t tr9{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    gmtr::Triangle_t tr10({{5, 5, 5}, {0, 0, 0}, {5, 0, 0}});
    gmtr::Plane_t plane4 = tr10.Triangle_Plane();
    gmtr::Plane_t plane5 = tr9.Triangle_Plane();
    gmtr::Line_t line1 = plane4.Planes_Intersection(plane5);
    gmtr::Line_t line2 = plane5.Planes_Intersection(plane4);

    ASSERT_TRUE(line1.point() == line2.point());
}

TEST(Point, Distance_to_Point) {
    gmtr::Point_t p1{1, 7, 9.6};
    gmtr::Point_t p2{-3, -2.4, 1};

    ASSERT_TRUE(std::abs(p1.Distance_to_Point(p2) - 13.353651) < gmtr::PRESISION);
}

TEST(Point, Distance_to_Plane) {
    gmtr::Point_t p1{0, 3, 6};
    gmtr::Point_t p2{0, 9, 5};
    gmtr::Plane_t pln{2, 4, -4, -6};
    ASSERT_TRUE(std::abs(p1.Distince_to_Plane(pln) + 3) < gmtr::PRESISION);
    ASSERT_TRUE(p1.Distince_to_Plane(pln) * p2.Distince_to_Plane(pln) < 0);
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

    ASSERT_TRUE(i3.Intersection_with_Interval(i4));

    gmtr::Interval_t i5{{0, 0, 0}, {2, 0, 0}};
    gmtr::Interval_t i6{{1, 0, 0}, {3, 0, 0}};

    ASSERT_TRUE(i5.Intersection_with_Interval(i6));
}

TEST(Line, Intersection_with_Triangle) {
    gmtr::Point_t p1{ 0, 0, 0};
    gmtr::Point_t p2{ 2, 4, 0};
    gmtr::Point_t p3{ 4, 0 ,0};
    gmtr::Line_t line{gmtr::Point_t{0, 2, 0}, gmtr::Point_t{4, 2, 0}};
    gmtr::Triangle_t triag{p1, p2, p3};

    gmtr::Interval_t res{{1, 2, 0}, {3, 2, 0}};

    gmtr::Interval_t inter = line.Intersection_with_Triangle(triag);

    ASSERT_EQ(res, inter);
}

TEST(Triangle, Triangles_Intersection) {
    gmtr::Point_t p000{0, 0, 0};
    gmtr::Point_t p240{2, 4, 0};
    gmtr::Point_t p400{4, 0, 0};
    gmtr::Point_t p210{2, 1, 0};
    gmtr::Point_t p230{2, 3, 0};
    gmtr::Point_t p420{4, 2, 0};
    gmtr::Point_t p110{1, 1, 0};
    gmtr::Point_t p112{1, 1, 2};
    gmtr::Point_t p100{1, 0, 0};
    gmtr::Point_t p010{0, 1, 0};

    gmtr::Point_t pnt1{0, 0, 0};
    gmtr::Point_t pnt2{1, 0, 0};
    gmtr::Point_t pnt3{0, 1, 0};

    gmtr::Point_t p2nt1{16, 31, 24};
    gmtr::Point_t p2nt2{16, 31, 26};
    gmtr::Point_t p2nt3{16, 33, 25};

    gmtr::Point_t p2_20{2, -2, 0},
                  p20_2{2, 0, -2},
                  p00_2{0, 0, -2},
                  p003{0, 0, 3};

    gmtr::Triangle_t tr1{p000, p240, p400};
    gmtr::Triangle_t tr2{p210, p230, p420};

    ASSERT_TRUE(tr1.Triangles_Intersection(tr2));

    gmtr::Triangle_t tr3{p000, p110, p112};
    gmtr::Triangle_t tr4{p100, p010, p112};

    ASSERT_TRUE(tr3.Triangles_Intersection(tr4));

    gmtr::Triangle_t tr5{pnt1, pnt2, pnt3};
    gmtr::Triangle_t tr6{p2nt1, p2nt2, p2nt3};

    ASSERT_FALSE(tr5.Triangles_Intersection(tr6));

    gmtr::Triangle_t tr7{p000, p2_20, p210},
                     tr8{p20_2, p00_2, p003};

    ASSERT_TRUE(tr7.Triangles_Intersection(tr8));
    ASSERT_TRUE(tr8.Triangles_Intersection(tr7));

    gmtr::Triangle_t tr9{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    gmtr::Triangle_t tr10({{5, 5, 5}, {0, 0, 0}, {5, 0, 0}});

    ASSERT_TRUE(tr9.Triangles_Intersection(tr10));

    gmtr::Triangle_t tr11{{0, 0, 0}, {2, 0, 0}, {0, 2, 0}};
    gmtr::Triangle_t tr12({{2, 0, 0}, {0, 0, 2}, {0, 1, 0}});

    ASSERT_TRUE(tr11.Triangles_Intersection(tr12));

    gmtr::Triangle_t tr13{{0, 0, 0}, {2, 0, 0}, {0, 2, 0}};
    gmtr::Triangle_t tr14({{0, 0, 2}, {2, 0, 0}, {4, 0, 0}});

    ASSERT_TRUE(tr13.Triangles_Intersection(tr14));

    //0 0 0 1 0 0 0 0 1
    //0.5 -0.5 0 0.5 0.5 0 0.5 0 1

    gmtr::Triangle_t tr17{{0, 0, 0}, {1, 0, 0}, {0, 0, 1}};
    gmtr::Triangle_t tr18{{0.5, -0.5, 0}, {0.5, 0.5, 0}, {0.5, 0, 1}};

    ASSERT_TRUE(tr17.Triangles_Intersection(tr18));
}


TEST(Line, Intersection_with_triangle) {
    gmtr::Point_t p20_2{2, 0, -2},
                  p00_2{0, 0, -2},
                  p003{0, 0, 3};
    gmtr::Triangle_t tr8{p20_2, p00_2, p003};
    gmtr::Line_t line{gmtr::Point_t{0, 0, 0}, gmtr::Vector_t{1, 0, 0}};
    gmtr::Interval_t trueRes{{0, 0, 0}, {1.2, 0, 0}};
    gmtr::Interval_t res = line.Intersection_with_Triangle(tr8);

    ASSERT_TRUE((trueRes.A() == res.A() && trueRes.B() == res.B()) ||
                         (trueRes.A() == res.B() && trueRes.B() == res.A()));
}

TEST( Triangle, Triangle_Intesection2) {
    gmtr::Triangle_t tr1{{1, 1, 0}, {1, 2 , 3}, { 5, 4, 8}};
    gmtr::Triangle_t tr2{{ 1, 1, 0}, {3, 1, 0}, {1, 3, 0}};

    ASSERT_TRUE(tr2.Triangles_Intersection(tr1));
    ASSERT_TRUE(tr1.Triangles_Intersection(tr2));
}

TEST( Triangle, Triangle_Intesection3) {
    gmtr::Triangle_t tr1{{81.9589, 6.52009, 49.2611}, {72.4774, -5.17581, 4.8547},  {67.4174, -32.2985, 51.3611}};
    gmtr::Triangle_t tr2{ {90.5719, 6.49289, 127.243},  {62.678, -18.4037, -50.2514},  {54.8061, -41.8008, -40.0074}};

    ASSERT_FALSE(tr2.Triangles_Intersection(tr1));
    ASSERT_FALSE(tr1.Triangles_Intersection(tr2));
}

TEST(Triangle, Triangle_Intersection4) {
    gmtr::Triangle_t tr1{{43.5664, 244.222, 105.83}, {1.23644, 215.836, -25.0299},  { 52.3174, 241.505, 105.388}};
    gmtr::Triangle_t tr2{ {173.485, 201.461, 97.8861},  {145.336, 211.758, 87.1047},  {195.226, 226.65, -6.50206}};

    ASSERT_FALSE(tr2.Triangles_Intersection(tr1));
    ASSERT_FALSE(tr1.Triangles_Intersection(tr2));
}

TEST(Triangle, Triangle_Intersection5) {
    gmtr::Triangle_t tr1{{213.151, 85.2705, 215.426}, {173.066, 117.913, 25.8474},  { 127.446, 155.34, 171.712}};
    gmtr::Triangle_t tr2{ {152.114, 139.092, 20.8334},  {114.902, 173.412, -14.8781},  { 57.384, 128.393, 117.213}};

    ASSERT_FALSE(tr2.Triangles_Intersection(tr1));
    ASSERT_FALSE(tr1.Triangles_Intersection(tr2));
}

TEST(Triangle, Triangle_Intersection6) {

//    -267.7 267.7 0
//    -227.215 267.7 0
//    -267.7 361.065 0
//
//    0 0 0
//    40.4847 0 0
//    0 93.3652 0

    gmtr::Triangle_t tr1{{-267.7, 267.7, 0}, {-227.215, 267.7, 0},  { -267.7, 361.065, 0}};
    gmtr::Triangle_t tr2{ {0, 0, 0},  {40.4847, 0, 0},  { 0, 93.3652, 0}};

    ASSERT_FALSE(tr2.Triangles_Intersection(tr1));
    ASSERT_FALSE(tr1.Triangles_Intersection(tr2));
}

TEST(Triangle, Triangle_INtersection7) {
//    2
//    0 0 0 1 0 0 0 1 0
//    0 0 0.01 5 5 0.01 5 5 -0.09

    gmtr::Triangle_t tr1{{0, 0, 0},
                         {1, 0, 0},
                         {0, 1, 0}};
    gmtr::Triangle_t tr2{{0, 0, 0.01},
                         {5, 5, 0.01},
                         {5, 5, -0.09}};
    ASSERT_TRUE(tr2.Triangles_Intersection(tr1));
    ASSERT_TRUE(tr1.Triangles_Intersection(tr2));
}

TEST(Triangle, Triangle_Intersection8) {
    gmtr::Triangle_t tr15{{-3, 0, 0}, {-1, 0, 0}, {-2, 0, 0}};
    gmtr::Triangle_t tr16{{0, -3, 0}, {0, 2, 0}, {-3, 0, 0}};

    ASSERT_TRUE(tr15.Triangles_Intersection(tr16));
    ASSERT_TRUE(tr16.Triangles_Intersection(tr15));
}

TEST(Tiangle, Triangle_Intersection9) {
    gmtr::Triangle_t tr1{{-1, 0, 0}, {-2, 0, 0}, {-3, 0, 0}};
    gmtr::Triangle_t tr2{{-2, -1, 0}, {-2, 1, 0}, {-2, 0, 0}};

    ASSERT_TRUE(tr1.Triangles_Intersection(tr2));
    ASSERT_TRUE(tr2.Triangles_Intersection(tr1));
}

TEST(Triangle, Triangle_Intersection10) {
//    2
//    1 1 0 3 1 0 1 3 0
//    1 1 0 1 2 3 5 4 8

    gmtr::Triangle_t tr1{{1, 1, 0}, {3, 1, 0}, {1, 3, 0}};
    gmtr::Triangle_t tr2{{1, 1, 0}, {1, 2, 3}, {5, 4, 8}};

    ASSERT_TRUE(tr1.Triangles_Intersection(tr2));
    ASSERT_TRUE(tr2.Triangles_Intersection(tr1));

}
#pragma once

#include <cmath>
#include <iostream>
#include <cassert>
#include <array>
#include <random>
#include "Triangle.h"

namespace gmtr {
    const double PRESISION = 0.00001;

    class Plane_t;
    class Triangle_t;
    class Vector_t;
    class Interval_t;
    class Point_t;


    double Determinate_2x2 (double a, double b, double c, double d);
    bool operator==(Point_t const& lhs, Point_t const& rhs);
    bool operator!=(Point_t const& lhs, Point_t const& rhs);
    bool operator==(Vector_t const& lhs, Vector_t const& rhs);
    bool operator==(Interval_t const& lhs, Interval_t const& rhs);
    int DoubleSign(double number);
    bool DoubleEqual(double rhs, double lhs);
    std::ostream &operator<<(std::ostream &os, Point_t point);

    class Point_t {
    public:
        double X() const {return x_;};
        double Y() const {return y_;};
        double Z() const {return z_;};

        Point_t() : x_(NAN), y_(NAN), z_(NAN) {}
        Point_t(double x, double y, double z) : x_(x), y_(y), z_(z) {}
        Point_t(Point_t const &point) = default;
        bool IsValid() const;

        double Distance_to_Point(Point_t other) const;
        double Distince_to_Plane(Plane_t plane) const;

        Vector_t Into_Vector() const;

        Point_t operator-(const Point_t& rhs) const;
        Point_t operator+(const Point_t& rhs) const;
        Point_t operator+(const Vector_t& rhs) const;

        friend std::istream& operator>>(std::istream& is, Point_t point);

    private:
        double x_;
        double y_;
        double z_;
    };

//---------------------------------------------------------------------------------------------------------

    class Vector_t {
    public:
        double X() const {return x_;};
        double Y() const {return y_;};
        double Z() const {return z_;};

        Vector_t() : x_(NAN), y_(NAN), z_(NAN) {}
        Vector_t(double x, double y, double z) : x_(x), y_(y),
                                                 z_(z) {}
        Vector_t(Point_t p1, Point_t p2);

        Vector_t Vector_Mult(const Vector_t& other) const;
        double Scalar_Mult(const Vector_t& other) const;
        double Length() const;

        bool IsValid() const;

        Vector_t operator-(Vector_t& other) const;
        std::ostream& operator<<(std::ostream& os) const;

        operator Point_t() const {return Point_t{x_, y_, z_};}
    private:
        double x_;
        double y_;
        double z_;
    };

//---------------------------------------------------------------------------------------------------------

    class Line_t {
    public:
        Point_t point() const {return point_;}
        Vector_t vector() const {return vector_;}

        Line_t() : point_(), vector_() {}
        Line_t(Point_t point, Vector_t vector) : point_(point), vector_(vector) {}
        Line_t(Point_t p1, Point_t p2) : point_(p1), vector_(p1, p2) {}

        Point_t Intersection_with_Line(Line_t other);
        Interval_t Intersection_with_Triangle(Triangle_t triangle);
        Point_t Intersection_with_Interval(Interval_t interval);

        bool IsValid();


    private:
        Point_t point_;
        Vector_t vector_;
    };

//---------------------------------------------------------------------------------------------------------

    class Plane_t {
    public:
        double A() const {return A_;}
        double B() const {return B_;}
        double C() const {return C_;}
        double D() const {return D_;}

        Plane_t() : A_(NAN), B_(NAN), C_(NAN), D_(NAN) {}
        Plane_t(double A, double B, double C, double D) : A_(A), B_(B),
                                                          C_(C), D_(D) {}

        Line_t Planes_Intersection(Plane_t& other);
        Vector_t n() const;
        bool IsCollinear(Plane_t other);

        bool IsValid() const;

        bool operator==(Plane_t& rhs) const;

    private:
        double A_;
        double B_;
        double C_;
        double D_;
    };

//---------------------------------------------------------------------------------------------------------

    class Triangle_t {
    public:
        Point_t A() const {return a_;}
        Point_t B() const {return b_;}
        Point_t C() const {return c_;}
        size_t Id() const {return id_;}

        double MinX();
        double MinY();
        double MinZ();

        double MaxX();
        double MaxY();
        double MaxZ();

        Triangle_t() : a_(), b_(), c_() {}
        Triangle_t(Point_t a, Point_t b, Point_t c) : a_(a), b_(b), c_(c), id_(0) {}
        Triangle_t(Point_t a, Point_t b, Point_t c, size_t id) : a_(a), b_(b), c_(c), id_(id) {}
        bool Triangles_Intersection(Triangle_t& other);
        bool IsDegenerate();
        bool Is_Triangle_Point(Point_t& point);

        bool IsValid();
        bool IsNormal();
        bool IsInterval();
        bool IsPoint();

        Plane_t Triangle_Plane();
        friend std::istream& operator>>(std::istream& is, Triangle_t triangle);

    private:
        Point_t b_;
        Point_t c_;
        Point_t a_;
        size_t id_;
    };

//----------------------------------------------------------------------------------

    class Interval_t {
    public:
        Point_t A() const {return a_;}
        Point_t B() const {return b_;}

        Interval_t() : a_{}, b_{} {}
        Interval_t(Point_t a, Point_t b) : a_(a), b_(b) {}
        bool Intersection_with_Interval(Interval_t other);
        bool Intersection_with_Triangle(Triangle_t triangle);
        bool is_Interval_Point(Point_t point);

        bool IsPoint() {return a_ == b_;}
        bool IsValid() {return a_.IsValid() && b_.IsValid();}

        Line_t Line() {return {a_, b_};}
    private:
        Point_t a_;
        Point_t b_;
    };

//--------------------------------------------------------------------------------------------------------------

    class Sphere_t {
    public:
        Sphere_t() : radius_{NAN}, centre_{} {}
        Sphere_t(double radius, Point_t centre)
                                :radius_{radius}, centre_{centre} {}
        Point_t Random_Point();
    private:
        double radius_;
        Point_t centre_;
    };

//--------------------------------------------------------------------------------------------------------------

}
#pragma once

#include <cmath>
#include <iostream>

namespace gmtr {

    const double PRESISION = 0.00001;

    class Point_t {
    public:
        double X() const {return x_;};
        double Y() const {return y_;};
        double Z() const {return z_;};

        Point_t() : x_(NAN), y_(NAN), z_(NAN) {}
        Point_t(double x, double y, double z) : x_(x), y_(y), z_(z) {};

        bool IsValid() const;

    private:
        double x_;
        double y_;
        double z_;
    };

    class Vector_t {
    public:
        double X() const {return x_;};
        double Y() const {return y_;};
        double Z() const {return z_;};

        Vector_t() : x_(NAN), y_(NAN), z_(NAN) {}
        Vector_t(double x, double y, double z) : x_(x), y_(y),
                                                 z_(z) {}

        Vector_t Vector_Mult(const Vector_t& other) const;
        double Scalar_Mult(const Vector_t& other) const;

        bool IsValid() const;

    private:
        double x_;
        double y_;
        double z_;
    };

    class Line_t {
    public:
        Point_t point() const {return point_;}
        Vector_t vector() const {return vector_;}

        Line_t() : point_(), vector_() {}
        Line_t(Point_t point, Vector_t vector) : point_(point), vector_(vector) {}

        bool IsValid();

    private:
        Point_t point_;
        Vector_t vector_;
    };

    class Plane_t {
    public:

        Plane_t() : A_(NAN), B_(NAN), C_(NAN), D_(NAN) {}
        Plane_t(double A, double B, double C, double D) : A_(A), B_(B),
                                                          C_(C), D_(D) {}

        Line_t Planes_Intersection(Plane_t& other);
        Vector_t n();

    private:
        double A_;
        double B_;
        double C_;
        double D_;
    };

    class Triangle_t {
    public:
        Point_t A() const {return a_;};
        Point_t B() const {return b_;};
        Point_t C() const {return c_;};

        Triangle_t() : a_(), b_(), c_() {}

        bool Triangles_Intersection(Triangle_t& other);
        Plane_t Triangle_Plane();

    private:
        Point_t a_;
        Point_t b_;
        Point_t c_;
    };

    double Determinate_2x2 (double a, double b, double c, double d);

    bool operator==( Vector_t  const& lhs, Vector_t const& rhs) ;
    bool operator==(Point_t const& lhs, Point_t const& rhs);
}
#pragma once

#include <cmath>

namespace gmtr {

    class Point_t {
    public:
        double X() const {return x_;};
        double Y() const {return y_;};
        double Z() const {return z_;};

        Point_t() : x_(NAN), y_(NAN), z_(NAN) {}


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

    private:
        double x_;
        double y_;
        double z_;
    };

    class Line_t {
    public:

        Line_t() : point_(), vector_() {}

    private:
        Point_t point_;
        Vector_t vector_{};
    };

    class Plane_t {
    public:

        Plane_t() : A_(NAN), B_(NAN), C_(NAN), D_(NAN) {}
        Plane_t(double A, double B, double C, double D) : A_(A), B_(B),
                                                          C_(C), D_(D) {}

        Line_t Planes_Intersection(Plane_t& other);

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
}
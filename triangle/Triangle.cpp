#include "Triangle.h"

namespace gmtr {
    bool Triangle_t::Triangles_Intersection(Triangle_t &other) {
        //TODO:: Triangles_Intersection
    }

    Plane_t Triangle_t::Triangle_Plane() {

        // x - ax  bx - ax  cx - ax //
        // y - ay  by - ay  cy - ay //  =  0
        // z - az  bz - az  cz - az //

        double A = Determinate_2x2( b_.Y() - a_.Y(), c_.Y() - a_.Y(),
                                     b_.Z() - a_.Z(), c_.Z() - a_.Z());
        double B = Determinate_2x2( b_.X() - a_.X(), c_.X() - a_.X(),
                                    b_.Z() - a_.Z(), c_.Z() - a_.Z());
        double C = Determinate_2x2( b_.X() - a_.X(), c_.X() - a_.X(),
                                    b_.Y() - a_.Y(), c_.Y()- a_.Y());
        double D = -( A*a_.X() + B*a_.Y() + C*a_.Z());
        return Plane_t{A, B, C, D};
    }

    double Determinate_2x2 (double a, double b, double c, double d) {
        // a b //
        // c d //
        return (a * d - b * c);
    }


    Line_t Plane_t::Planes_Intersection(Plane_t &other) {
        Vector_t n1{A_, B_, C_};
        Vector_t n2{other.A_, other.B_, other.C_};
        double D1 = D_;
        double D2 = other.D_;
        double denominator = n1.Scalar_Mult(n2) * n1.Scalar_Mult(n2) - n1.Scalar_Mult(n1) * n2.Scalar_Mult(n2);
        if (denominator == 0) {
            return Line_t{};
        } else {
            double a = (D2 * n1.Scalar_Mult(n2) - D1 * n2.Scalar_Mult(n2)) /
                       denominator;
            double b = (D1 * n1.Scalar_Mult(n2) - D2 * n2.Scalar_Mult(n2)) /
                       denominator;
        }

    }

    Vector_t Vector_t::Vector_Mult(const Vector_t &other) const {
        Vector_t res;
        res.x_ = y_ * other.z_ - other.y_ * z_;
        res.y_ = x_ * other.z_ - other.x_ * z_;
        res.z_ = x_ * other.y_ - other.x_ * y_;
        return res;
    }

    double Vector_t::Scalar_Mult(const Vector_t &other) const {
        double res = x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
        return res;
    }
}
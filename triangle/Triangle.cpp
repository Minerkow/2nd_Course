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
        double D1 = D_;
        double D2 = other.D_;
        double denominator = n().Scalar_Mult(other.n()) * n().Scalar_Mult(other.n()) -
                             n().Scalar_Mult(n()) * other.n().Scalar_Mult(other.n());
        if (denominator == 0) {
            return Line_t{};
        }
        double a = (D2 * n().Scalar_Mult(other.n()) - D1 * other.n().Scalar_Mult(other.n())) /
                   denominator;
        double b = (D1 * n().Scalar_Mult(other.n()) - D2 * other.n().Scalar_Mult(other.n())) /
                   denominator;

        double r_x = a * n().X() + b * other.n().X();
        double r_y = a * n().Y() + b * other.n().Y();
        double r_z = a * n().Z() + b * other.n().Z();
        Point_t point{r_x, r_y, r_z};

        return Line_t{point, n().Vector_Mult(other.n())};
    }

    Vector_t Plane_t::n() {
        return Vector_t{A_, B_, C_};
    }

    Vector_t Vector_t::Vector_Mult(const Vector_t &other) const {
        Vector_t res;
        res.x_ = y_ * other.z_ - other.y_ * z_;
        res.y_ = - x_ * other.z_ + other.x_ * z_;
        res.z_ = x_ * other.y_ - other.x_ * y_;
        return res;
    }

    double Vector_t::Scalar_Mult(const Vector_t &other) const {
        double res = x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
        return res;
    }

    bool Vector_t::IsValid() const {
        return !(std::isnan(x_) || std::isnan(y_) || std::isnan(z_));
        ;
    }

    bool Line_t::IsValid() {
        return point_.IsValid() && vector_.IsValid();
    }


    bool Point_t::IsValid() const {
        return !(std::isnan(x_) || std::isnan(y_) || std::isnan(z_));
    }


    bool operator==(Vector_t const& lhs, Vector_t const& rhs) {
        return (lhs.X() <= rhs.X() + PRESISION && lhs.X() >= rhs.X() - PRESISION) &&
               (lhs.Y() <= rhs.Y() + PRESISION && lhs.Y() >= rhs.Y() - PRESISION) &&
               (lhs.Z() <= rhs.Z() + PRESISION && lhs.Z() >= rhs.Z() - PRESISION);
    }

    bool operator==(Point_t const& lhs, Point_t const& rhs) {
        return (lhs.X() <= rhs.X() + PRESISION && lhs.X() >= rhs.X() - PRESISION) &&
               (lhs.Y() <= rhs.Y() + PRESISION && lhs.Y() >= rhs.Y() - PRESISION) &&
               (lhs.Z() <= rhs.Z() + PRESISION && lhs.Z() >= rhs.Z() - PRESISION);
    }
}
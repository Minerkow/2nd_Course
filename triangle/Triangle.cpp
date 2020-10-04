#include "Triangle.h"

namespace gmtr {
    bool Triangle_t::Triangles_Intersection(Triangle_t &other) {
        Plane_t plane1 = other.Triangle_Plane();

        if (std::signbit(a_.Distince_to_Plane(plane1)) == std::signbit(b_.Distince_to_Plane(plane1)) &&
            std::signbit(a_.Distince_to_Plane(plane1)) == std::signbit(c_.Distince_to_Plane(plane1)))
            return false;

        Plane_t plane0 = Triangle_Plane();

        if (plane0.IsCollinear(plane1)) {
            if (std::abs(plane0.D() - plane1.D()) < PRESISION) {
                Interval_t i1{a_, b_};
                Interval_t i2{a_, c_};
                Interval_t i3{b_, c_};

                return i1.Intersection_with_Interval(i2) &&
                        i1.Intersection_with_Interval(i3) &&
                        i2.Intersection_with_Interval(i3);
            } else {
                return false;
            }
        }

        if (std::signbit( other.a_.Distince_to_Plane(plane0)) == std::signbit(other.b_.Distince_to_Plane(plane0)) &&
            std::signbit( other.a_.Distince_to_Plane(plane0)) == std::signbit(other.c_.Distince_to_Plane(plane0)))
            return false;

        Line_t interLine = plane1.Planes_Intersection(plane0);
        if (interLine.IsValid()) {

        }
        return false;
    }

//-----------------------------------------------------------------------------

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

//------------------------------------------------------------------------------


    bool Triangle_t::IsDegenerate() {
        Vector_t v1(a_, b_);
        Vector_t v2(a_, c_);
        if (v1.Vector_Mult(v2) == Vector_t{0, 0, 0}) {
            return true;
        } else {
            return false;
        }
    }

//-----------------------------------------------------------------------------

    double Determinate_2x2 (double a, double b, double c, double d) {
        // a b //
        // c d //
        return (a * d - b * c);
    }

//-----------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------

    Vector_t Plane_t::n() {
        return Vector_t{A_, B_, C_};
    }

//-----------------------------------------------------------------------------------------------

    bool Plane_t::operator==(Plane_t &rhs) const{
        return (A_ <= rhs.A_ + PRESISION && A_ >= rhs.A_ - PRESISION) &&
               (B_ <= rhs.B_ + PRESISION && B_ >= rhs.B_ - PRESISION) &&
               (C_ <= rhs.C_ + PRESISION && C_ >= rhs.C_ - PRESISION) &&
               (D_ <= rhs.D_ + PRESISION && D_ >= rhs.D_ - PRESISION);
    }

    bool Plane_t::IsCollinear(Plane_t other) const {
        return (A_ <= other.A_ + PRESISION && A_ >= other.A_ - PRESISION) &&
               (B_ <= other.B_ + PRESISION && B_ >= other.B_ - PRESISION) &&
               (C_ <= other.C_ + PRESISION && C_ >= other.C_ - PRESISION);
    }

//------------------------------------------------------------------------------------------------

    Vector_t Vector_t::Vector_Mult(const Vector_t &other) const {
        Vector_t res;
        res.x_ = y_ * other.z_ - other.y_ * z_;
        res.y_ = - x_ * other.z_ + other.x_ * z_;
        res.z_ = x_ * other.y_ - other.x_ * y_;
        return res;
    }

//------------------------------------------------------------------------------------------------

    double Vector_t::Scalar_Mult(const Vector_t &other) const {
        double res = x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
        return res;
    }

//-----------------------------------------------------------------------------------------------

    bool Vector_t::IsValid() const {
        return !(std::isnan(x_) || std::isnan(y_) || std::isnan(z_));
        ;
    }

//------------------------------------------------------------------------------------------------

    Vector_t::Vector_t(Point_t p1, Point_t p2) {
        x_ = p2.X() - p1.X();
        y_ = p2.Y() - p1.Y();
        z_ = p2.Z() - p1.Z();
    }

//-----------------------------------------------------------------------------------------------

    Vector_t Vector_t::operator-(Vector_t &other) const{
        return Vector_t{x_ - other.x_, y_ - other.y_, z_ - other.z_};
    }

//----------------------------------------------------------------------------------------------

    double Vector_t::Length() const {
        return std::sqrt(x_*x_ + y_*y_ + z_*z_);
    }

//----------------------------------------------------------------------------------------------

    std::ostream& Vector_t::operator<<(std::ostream &os) const {
        os << "{" << x_ << " " << y_ << " " << z_ << "}\n";
        return os;
    }

//----------------------------------------------------------------------------------------------

    bool Line_t::IsValid() {
        return point_.IsValid() && vector_.IsValid();
    }

//-----------------------------------------------------------------------------------------------

    Point_t Line_t::Intersection_with_Line(Line_t other) {
        //TODO::General
        //L1 = p1 + t1*g1
        //L2 = p2 + t2*g2
        //p1 + t1*g1 = p2 + t2*g2 | x g1
        //t2*[g2; g1] = [p1 - p2; g1]
        //t1*[g1; g2] = [p2 - p1; g2]
        Vector_t p1 = point_.Into_Vector();
        Vector_t p2 = other.point_.Into_Vector();
        Vector_t g1 = vector_;
        Vector_t g2 = other.vector_;

        if (g1.Vector_Mult(g2) == Vector_t{0, 0, 0}) {
            if (p1 == p2) {
                return Point_t{0, 0 , NAN};
            } else {
                return Point_t{};
            }
        }
        double t1;
        if (g1.Vector_Mult(g2).X() != 0 && (p2 - p1).Vector_Mult(g2).X() != 0) {
            t1 = (p2 - p1).Vector_Mult(g2).X() /
                        g1.Vector_Mult(g2).X();
        }
        if (g1.Vector_Mult(g2).Y() != 0 && (p2 - p1).Vector_Mult(g2).Y() != 0) {
            t1 = (p2 - p1).Vector_Mult(g2).Y() /
                        g1.Vector_Mult(g2).Y();
        }
        if (g1.Vector_Mult(g2).Z() != 0 && (p2 - p1).Vector_Mult(g2).Z() != 0) {
            t1 = (p2 - p1).Vector_Mult(g2).Z() /
                        g1.Vector_Mult(g2).Z();
        }

        Point_t res{p1.X()+t1*g1.X(), p1.Y()+t1*g1.Y(), p1.Z()+t1*g1.Z()};
        return res;
    }

    Interval_t Line_t::Intersection_with_Triangle(Triangle_t triangle) {
                
    }

//--------------------------------------------------------------------------------------------

    bool Point_t::IsValid() const {
        return !(std::isnan(x_) || std::isnan(y_) || std::isnan(z_));
    }

    double Point_t::Distance_to_Point(Point_t other) const{
        double res = std::sqrt((x_ - other.x_) * (x_ - other.x_) +
                               (y_ - other.y_) * (y_ - other.y_) +
                                (z_ - other.z_) * (z_ - other.z_));
        return res;
    }

//-------------------------------------------------------------------------------------------

    Point_t Point_t::operator-(const Point_t& rhs) const {
        return Point_t{x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_};
    }

//-------------------------------------------------------------------------------------------

    double Point_t::Distince_to_Plane(Plane_t plane) const {
        double res = (plane.A()*x_ + plane.B()*y_ + plane.C()*z_ + plane.D()) /
                    std::sqrt(plane.A()*plane.A() + plane.B()*plane.B() + plane.C()*plane.C());
        return res;
    }

//-------------------------------------------------------------------------------------------

    Vector_t Point_t::Into_Vector() const{
        return Vector_t{x_, y_, z_};
    }

//-------------------------------------------------------------------------------------------

    std::ostream& Point_t::operator<<(std::ostream &os) const {
        os << "[" << x_ << " " << y_ << " " << z_ << "]\n";
        return os;
    }

//-------------------------------------------------------------------------------------------

    bool operator==(Vector_t const& lhs, Vector_t const& rhs) {
        return (lhs.X() <= rhs.X() + PRESISION && lhs.X() >= rhs.X() - PRESISION) &&
               (lhs.Y() <= rhs.Y() + PRESISION && lhs.Y() >= rhs.Y() - PRESISION) &&
               (lhs.Z() <= rhs.Z() + PRESISION && lhs.Z() >= rhs.Z() - PRESISION);
    }

//-------------------------------------------------------------------------------------------

    bool operator==(Point_t const& lhs, Point_t const& rhs) {
        return (lhs.X() <= rhs.X() + PRESISION && lhs.X() >= rhs.X() - PRESISION) &&
               (lhs.Y() <= rhs.Y() + PRESISION && lhs.Y() >= rhs.Y() - PRESISION) &&
               (lhs.Z() <= rhs.Z() + PRESISION && lhs.Z() >= rhs.Z() - PRESISION);
    }

//-------------------------------------------------------------------------------------------

    bool Interval_t::Intersection_with_Interval(Interval_t other) {
        Line_t line1{a_, b_};
        if (!line1.IsValid()) {
            exit(2);
        }
        Line_t line2{other.a_, other.b_};
        if (!line2.IsValid()) {
            exit(2);
        }
        Point_t intersecPoint = line1.Intersection_with_Line(line2);
        //std::cerr << intersecPoint.X() << " " << intersecPoint.Y() << " " << intersecPoint.Z();
        if (!intersecPoint.IsValid()) {
            return false;
        }
        if (is_Interval_Point(intersecPoint) &&
            other.is_Interval_Point(intersecPoint)) {
            return true;
        } else {
            return false;
        }
    }

//-------------------------------------------------------------------------------------------

    bool Interval_t::is_Interval_Point(Point_t point) {
        Vector_t vec1{a_, point};
        Vector_t vec2{b_, point};
        if (vec1.Vector_Mult(vec2) == Vector_t{0, 0, 0} &&
            vec1.Scalar_Mult(vec2) <= 0.0) {
            return true;
        } else {
            return false;
        }
    }
}
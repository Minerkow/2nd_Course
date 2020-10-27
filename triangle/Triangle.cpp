#include "Triangle.h"


namespace gmtr {
    bool Triangle_t::Triangles_Intersection(Triangle_t &other) {

        if (!IsNormal() && !other.IsNormal()) {
            Point_t a1, b1;
            if (a_ != b_) {
                a1 = a_;
                b1 = b_;
            } else {
                a1 = a_;
                b1 = c_;
            }
            Interval_t interval1{a1, b1};
            Point_t a2, b2;
            if (other.a_ != other.b_) {
                a2 = other.a_;
                b2 = other.b_;
            } else {
                a2 = other.a_;
                b2 = other.c_;
            }
            Interval_t interval2{a2, b2};
            return interval1.Intersection_with_Interval(interval2);
        }


        if (!IsNormal()) {
            Point_t a, b;
            if (a_ != b_) {
                a = a_;
                b = b_;
            } else {
                a = a_;
                b = c_;
            }
            Interval_t interval{a, b};
            return interval.Intersection_with_Triangle(other);
        }

        if (!IsNormal()) {
            Point_t a, b;
            if (a_ != b_) {
                a = other.a_;
                b = other.b_;
            } else {
                a = other.a_;
                b = other.c_;
            }
            Interval_t interval{a, b};
            return interval.Intersection_with_Triangle(*this);
        }

        Plane_t plane1 = other.Triangle_Plane();

        double DistA = a_.Distince_to_Plane(plane1);
        double DistB = b_.Distince_to_Plane(plane1);
        double DistC = c_.Distince_to_Plane(plane1);

        if (DoubleSign(DistA) == DoubleSign(DistB) &&
            DoubleSign(DistA) == DoubleSign(DistC) && DoubleSign(DistA) != 0) {
            return false;
        }

        Plane_t plane0 = Triangle_Plane();
        if (plane0.IsCollinear(plane1)) {
            if (std::abs(plane0.D() - plane1.D()) <= PRESISION) {
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

        DistA = other.a_.Distince_to_Plane(plane0);
        DistB = other.b_.Distince_to_Plane(plane0);
        DistC = other.c_.Distince_to_Plane(plane0);

        if (DoubleSign(DistA) == DoubleSign(DistB) &&
            DoubleSign(DistA) == DoubleSign(DistC) && DoubleSign(DistA) != 0) {
            return false;
        }

        Line_t interLine = plane1.Planes_Intersection(plane0);
        if (interLine.IsValid()) {
            Interval_t interval1 = interLine.Intersection_with_Triangle(*this);
            Interval_t interval2 = interLine.Intersection_with_Triangle(other);
            return interval1.Intersection_with_Interval(interval2);
        }
        return false;
    }

//-----------------------------------------------------------------------------

    Plane_t Triangle_t::Triangle_Plane() {

        // x - ax  bx - ax  cx - ax //
        // y - ay  by - ay  cy - ay //  =  0
        // z - az  bz - az  cz - az //

        double A = Determinate_2x2(b_.Y() - a_.Y(), c_.Y() - a_.Y(),
                                   b_.Z() - a_.Z(), c_.Z() - a_.Z());
        if (DoubleEqual(A, 0)) {
            A = 0;
        }
        double B = -Determinate_2x2(b_.X() - a_.X(), c_.X() - a_.X(),
                                   b_.Z() - a_.Z(), c_.Z() - a_.Z());
        if (DoubleEqual(B, 0)) {
            B = 0;
        }
        double C = Determinate_2x2(b_.X() - a_.X(), c_.X() - a_.X(),
                                   b_.Y() - a_.Y(), c_.Y() - a_.Y());
        if (DoubleEqual(C, 0)) {
            C = 0;
        }
        double D = -(A * a_.X() + B * a_.Y() + C * a_.Z());
        if (DoubleEqual(D, 0)) {
            D = 0;
        }

        double maxCoeff = std::max(std::max(std::abs(A), std::abs(B)), std::max(std::abs(C), std::abs(D)));

        return Plane_t{A/maxCoeff , B/maxCoeff, C/maxCoeff, D/maxCoeff};
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

    std::istream& operator>>(std::istream &is, Triangle_t triangle) {
        is >> triangle.a_ >> triangle.b_ >> triangle.c_;
        return is;
    }

    double Triangle_t::MinX() {
        return std::min(a_.X(), std::min(b_.X(), c_.X()));
    }

    double Triangle_t::MinY() {
        return std::min(a_.Y(), std::min(b_.Y(), c_.Y()));
    }

    double Triangle_t::MinZ() {
        return std::min(a_.Z(), std::min(b_.Z(), c_.Z()));
    }

    double Triangle_t::MaxX() {
        return std::max(a_.X(), std::max(b_.X(), c_.X()));
    }

    double Triangle_t::MaxY() {
        return std::max(a_.Y(), std::max(b_.Y(), c_.Y()));
    }

    double Triangle_t::MaxZ() {
        return std::max(a_.Z(), std::max(b_.Z(), c_.Z()));
    }

    bool Triangle_t::IsValid() {
        return a_.IsValid() && b_.IsValid() && c_.IsValid();
    }

    bool Triangle_t::IsNormal() {
        return Triangle_Plane().IsValid();
    }

    bool Triangle_t::IsInterval() {
        if (IsPoint()) {
            return false;
        }
        if (b_ == c_ || a_ == b_ || a_ == c_) {
            return true;
        } else {
            return false;
        }
    }

    bool Triangle_t::IsPoint() {
        if (b_ == c_ && a_ == b_) {
            return true;
        } else {
            return false;
        }
    }

//-----------------------------------------------------------------------------

    double Determinate_2x2(double a, double b, double c, double d) {
        // a b //
        // c d //
        return (a * d - b * c);
    }

//-----------------------------------------------------------------------------

    Line_t Plane_t::Planes_Intersection(Plane_t &other) {
        double S1 = -D_;
        double S2 = -other.D_;
        double denominator = n().Scalar_Mult(other.n()) * n().Scalar_Mult(other.n()) -
                             n().Scalar_Mult(n()) * other.n().Scalar_Mult(other.n());
        if (denominator == 0) {
            return Line_t{};
        }
        double a = (S2 * n().Scalar_Mult(other.n()) - S1 * other.n().Scalar_Mult(other.n())) /
                   denominator;
        double b = (S1 * n().Scalar_Mult(other.n()) - S2 * n().Scalar_Mult(n())) /
                   denominator;

        double r_x = a * n().X() + b * other.n().X();
        double r_y = a * n().Y() + b * other.n().Y();
        double r_z = a * n().Z() + b * other.n().Z();
        Point_t point{r_x, r_y, r_z};

        return Line_t{point, n().Vector_Mult(other.n())};
    }

//----------------------------------------------------------------------------------------------

    Vector_t Plane_t::n() const {
        return Vector_t{A_, B_, C_};
    }

//-----------------------------------------------------------------------------------------------

    bool Plane_t::operator==(Plane_t &rhs) const {
        return (A_ <= rhs.A_ + PRESISION && A_ >= rhs.A_ - PRESISION) &&
               (B_ <= rhs.B_ + PRESISION && B_ >= rhs.B_ - PRESISION) &&
               (C_ <= rhs.C_ + PRESISION && C_ >= rhs.C_ - PRESISION) &&
               (D_ <= rhs.D_ + PRESISION && D_ >= rhs.D_ - PRESISION);
    }

    bool Plane_t::IsCollinear(Plane_t other) {
        if (other.n().Vector_Mult(n()) == Vector_t{0, 0, 0}) {
            return true;
        } else {
            return false;
        }
    }

    bool Plane_t::IsValid() const {
        return !std::isnan(A_*B_*C_*D_);
    }


//------------------------------------------------------------------------------------------------

    Vector_t Vector_t::Vector_Mult(const Vector_t &other) const {
        Vector_t res;
        res.x_ = y_ * other.z_ - other.y_ * z_;
        res.y_ = -x_ * other.z_ + other.x_ * z_;
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
    }

//------------------------------------------------------------------------------------------------

    Vector_t::Vector_t(Point_t p1, Point_t p2) {
        x_ = p2.X() - p1.X();
        y_ = p2.Y() - p1.Y();
        z_ = p2.Z() - p1.Z();
    }

//-----------------------------------------------------------------------------------------------

    Vector_t Vector_t::operator-(Vector_t &other) const {
        return Vector_t{x_ - other.x_, y_ - other.y_, z_ - other.z_};
    }

//----------------------------------------------------------------------------------------------

    double Vector_t::Length() const {
        return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

//----------------------------------------------------------------------------------------------

    std::ostream &Vector_t::operator<<(std::ostream &os) const {
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
            return Point_t{0, 0, NAN};
        }
        double t1 = 0;
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

        Point_t res{p1.X() + t1 * g1.X(), p1.Y() + t1 * g1.Y(), p1.Z() + t1 * g1.Z()};
        return res;
    }

    Point_t Line_t::Intersection_with_Interval(Interval_t interval) {
        Point_t point = Intersection_with_Line(interval.Line());
        if (point.IsValid() && interval.is_Interval_Point(point)) {
            return point;
        }
        return Point_t{};
    }

    Interval_t Line_t::Intersection_with_Triangle(Triangle_t triangle) {
        Point_t p1 = Intersection_with_Interval({triangle.A(), triangle.B()});
        Point_t p2 = Intersection_with_Interval({triangle.A(), triangle.C()});
        Point_t p3 = Intersection_with_Interval({triangle.B(), triangle.C()});

        if (p1.IsValid() && p2.IsValid()) {
            return {p1, p2};
        }

        if (p1.IsValid() && p3.IsValid()) {
            return {p1, p3};
        }

        if (p2.IsValid() && p3.IsValid()) {
            return {p2, p3};
        }

        if (p1.IsValid() && !p2.IsValid() && !p3.IsValid()) {
            return {p1, p1};
        }

        if (p2.IsValid() && !p1.IsValid() && !p3.IsValid()) {
            return {p2, p2};
        }

        if (p3.IsValid() && !p1.IsValid() && !p2.IsValid()) {
            return {p3, p3};
        }

        if (!p1.IsValid() && !p2.IsValid() && !p3.IsValid()) {
            return {p1, p1};
        }
        assert(false && "Interscetion with triangle oooops");
    }


//--------------------------------------------------------------------------------------------

    bool Point_t::IsValid() const {
        return !(std::isnan(x_) || std::isnan(y_) || std::isnan(z_));
    }

    double Point_t::Distance_to_Point(Point_t other) const {
        double res = std::sqrt((x_ - other.x_) * (x_ - other.x_) +
                               (y_ - other.y_) * (y_ - other.y_) +
                               (z_ - other.z_) * (z_ - other.z_));
        return res;
    }

//-------------------------------------------------------------------------------------------

    Point_t Point_t::operator-(const Point_t &rhs) const {
        return Point_t{x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_};
    }

//-------------------------------------------------------------------------------------------

    double Point_t::Distince_to_Plane(Plane_t plane) const {
        double res = (plane.A() * x_ + plane.B() * y_ + plane.C() * z_ + plane.D()) /
                     std::sqrt(plane.A() * plane.A() + plane.B() * plane.B() + plane.C() * plane.C());
        return res;
    }

//-------------------------------------------------------------------------------------------

    Vector_t Point_t::Into_Vector() const {
        return Vector_t{x_, y_, z_};
    }

//-------------------------------------------------------------------------------------------

    std::ostream &operator<<(std::ostream &os, Point_t point) {
        os  << point.X() << " " << point.Y() << " " << point.Z() << " ";
        return os;
    }

    std::istream& operator>>(std::istream & is, Point_t point) {
        is >> point.x_ >> point.y_ >> point.z_;
        return is;
    }

    Point_t Point_t::operator+(const Point_t& rhs) const {
        return Point_t{x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_};
    }

    Point_t Point_t::operator+(const Vector_t &rhs) const {
        return Point_t{x_ + rhs.X(), y_ + rhs.Y(), z_ + rhs.Y()};
    }



//-------------------------------------------------------------------------------------------

    bool operator==(Vector_t const &lhs, Vector_t const &rhs) {

        return DoubleEqual(lhs.X(), rhs.X())  &&
               DoubleEqual(lhs.Y(), rhs.Y()) &&
               DoubleEqual(lhs.Z(), rhs.Z());
    }

    bool operator==(Point_t const &lhs, Point_t const &rhs) {

        return DoubleEqual(lhs.X(), rhs.X())  &&
               DoubleEqual(lhs.Y(), rhs.Y()) &&
               DoubleEqual(lhs.Z(), rhs.Z());
    }

    bool operator==(Interval_t const &lhs, Interval_t const &rhs) {
        return (lhs.A() == rhs.A() && lhs.B() == rhs.B()) ||
               (lhs.A() == rhs.B() && lhs.B() == rhs.A());
    }


//-------------------------------------------------------------------------------------------

    bool Interval_t::Intersection_with_Interval(Interval_t other) {
        if (!IsValid() || !other.IsValid()) {
            return false;
        }

        if (a_ == b_ && other.a_ == other.b_) {
            return a_ == other.a_;
        }
        if (a_ == b_) {
            return other.is_Interval_Point(a_);
        }

        if (other.a_ == other.b_) {
            return is_Interval_Point(other.b_);
        }

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
        if (std::isnan(intersecPoint.Z()) && !std::isnan(intersecPoint.X())) {
            return is_Interval_Point(other.a_) ||
                   is_Interval_Point(other.b_) ||
                   other.is_Interval_Point(a_) ||
                   other.is_Interval_Point(b_);
        }
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

    bool Interval_t::Intersection_with_Triangle(Triangle_t triangle) {
        if (IsPoint()) {
            return triangle.Is_Triangle_Point(a_);
        }
        Interval_t crossInterval = Line().Intersection_with_Triangle(triangle);
        if (!crossInterval.IsValid()) {
            return false;
        }
        return Intersection_with_Interval(crossInterval);
    }


//---------------------------------------------------------------------------------------------

    int DoubleSign(double number) {
        if (DoubleEqual(0, number)) {
            return 0;
        }
        if (number > 0) {
            return 1;
        }
        if (number < 0) {
            return -1;
        }
    }

    bool DoubleEqual(double rhs, double lhs) {
        return std::abs(rhs - lhs) < PRESISION;
    }


    Point_t Sphere_t::Random_Point() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis{-radius_, radius_};

        double dist = radius_ + 1;
        double x, y;
        while (dist > radius_) {
            x = dis(gen);
            y = dis(gen);
            dist = sqrt(x*x + y*y);
        }
        double z = std::sqrt(radius_ * radius_ - x*x - y*y);
        if (dis(gen) < 0) {
            z = -z;
        }
        return centre_ + Point_t{x, y, z};
    }

    bool operator!=(Point_t const& lhs, Point_t const& rhs){
        return !(lhs == rhs);
    }

    bool Triangle_t::Is_Triangle_Point(Point_t& point) {
        Plane_t plane = Triangle_Plane();
        if( point.Distince_to_Plane(plane) == 0 &&
            point.X() <= MaxX() && point.X() >= MinX() &&
            point.Y() <= MaxY() && point.Y() >= MinY() &&
            point.Z() <= MaxZ() && point.Z() >= MinZ() ) {
            return true;
        } else {
            return false;
        }
    }
}

//--------------------------------------------------------------------------------------------------------



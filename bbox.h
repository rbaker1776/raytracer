#ifndef BBOX_H_021A71223113608A
#define BBOX_H_021A71223113608A


#include <limits>
#include <algorithm>
#include "vector3.h"


class Interval
{
private:
    double lo;
    double hi;

public:
    Interval(double lo, double hi): lo(lo), hi(hi) {}

    bool does_include(double d) const { return d >= lo && d <= hi; }

    void grow_to_include(const Interval& i) { lo = std::fmin(lo, i.lo); hi = std::fmax(hi, i.hi); }

    static double clamp(double d, double lo, double hi) { return std::fmin(std::fmax(d, lo), hi); }

    static Interval include(double a, double b) { return Interval(std::fmin(a, b), std::fmax(a, b)); }
    static Interval world() { return Interval(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()); }
    static Interval empty() { return Interval(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity()); }
};


class BBox
{
private:
    Interval x;
    Interval y;
    Interval z;

public:
    BBox(const Interval& x = Interval::empty(), const Interval& y = Interval::empty(), const Interval& z = Interval::empty()):
            x(x), y(y), z(z)
    {}
    BBox(const Point3& p, const Point3& q):
        x(Interval::include(p.x, q.x)), y(Interval::include(p.y, q.y)), z(Interval::include(p.z, q.z))
    {}

    void grow_to_include(const BBox& box)
    {
        x.grow_to_include(box.x);
        y.grow_to_include(box.y);
        z.grow_to_include(box.z);
    }

    static BBox empty() { return BBox(Interval::empty(), Interval::empty(), Interval::empty()); }
    static BBox world() { return BBox(Interval::world(), Interval::world(), Interval::world()); }
};


#endif // BBOX_H_021A71223113608A

#ifndef AABB_H_56991BC118A0B718
#define AABB_H_56991BC118A0B718

#include "interval.h"
#include "vector3.h"


struct AABB
{
    Interval x;
    Interval y;
    Interval z;

    AABB(const Interval& x, const Interval& y, const Interval& z): x(x), y(y), z(z) {}

    void grow_to_include(const Point3& p) { x.grow_to_include(p.x); y.grow_to_include(p.y); z.grow_to_include(p.z); }

    Interval longest_axis() const { return x.size() > y.size() ? (x.size() > z.size() ? x : z) : (y.size() > z.size() ? y : z); }

    static AABB world() { return AABB(Interval::world(), Interval::world(), Interval::world()); }
    static AABB empty() { return AABB(Interval::empty(), Interval::empty(), Interval::empty()); }
};


#endif // AABB_H_56991BC118A0B718

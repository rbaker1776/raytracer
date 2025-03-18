#ifndef INTERVAL_H_04C1F3AEC057D6BD
#define INTERVAL_H_04C1F3AEC057D6BD

#include <algorithm>
#include "fputils.h"


struct Interval
{
    double lo;
    double hi;

    Interval(double lo, double hi): lo(lo), hi(hi) {}

    bool does_include(double d) const { return d >= lo && d <= hi; }

    void set_max(double d) { hi = d; }
    void grow_to_include(const Interval& i) { lo = std::min(lo, i.lo); hi = std::max(hi, i.hi); }

    static double clamp(double d, double lo, double hi) { return std::min(std::max(d, lo), hi); }

    static Interval include(double a, double b) { return Interval(std::min(a, b), std::max(a, b)); }
    static Interval world() { return Interval(-FPUtils::infinity(), FPUtils::infinity()); }
    static Interval empty() { return Interval(FPUtils::infinity(), -FPUtils::infinity()); }
};


#endif // INTERVAL_H_04C1F3AEC057D6BD

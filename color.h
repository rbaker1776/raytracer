#ifndef COLOR_H_5F0626917B33E5F7
#define COLOR_H_5F0626917B33E5F7

#include <cmath>
#include "vector3.h"
#include "interval.h"


struct Color: public Vector3
{
private:
    static constexpr double gamma { 2.2 };

public:
    Color(double r, double g, double b):
        Vector3(Interval::clamp(r, 0.0, 1.0), Interval::clamp(g, 0.0, 1.0), Interval::clamp(b, 0.0, 1.0))
    {}
    Color(const Vector3& v):
        Vector3(Interval::clamp(v.x, 0.0, 1.0), Interval::clamp(v.y, 0.0, 1.0), Interval::clamp(v.z, 0.0, 1.0))
    {}

    Vector3 operator*(const double s) const { return Vector3(x * s, y * s, z * s); }

    Color operator+(const Color& c) const { return Color(x + c.x, y + c.y, z + c.z); }

    Color operator*(const Color& c) const { return Color(x * c.x, y * c.y, z * c.z); }
    Color& operator*=(const Color& c) { return *this = *this * c; } 

    Color gamma_correct() const { return Color(std::pow(x, 1.0 / Color::gamma), std::pow(y, 1.0 / gamma), std::pow(z, 1.0 / gamma)); }
    Color gamma_uncorrect() const { return Color(std::pow(x, Color::gamma), std::pow(y, Color::gamma), std::pow(z, Color::gamma)); }

    inline static Color HSL(double h, double s, double l);
};


inline Color Color::HSL(double h, double s, double l)
{
    double r, g, b;

    auto hue_to_rgb { [](double p, double q, double t)
    {
        if (t < 0) { ++t; }
        if (t > 1) { --t; }
        if (t < 1.0 / 6.0) { return p + (q - p) * 6.0 * t; }
        if (t < 1.0 / 2.0) { return q; }
        if (t < 2.0 / 3.0) { return p + (q - p) * 6.0 * (2.0 / 3.0 - t); }
        return p;
    } };

    const double q { l < 0.5 ? l * (1 + s) : (l + s) - (l * s) };
    const double p { 2 * q - l };

    r = hue_to_rgb(p, q, h + 1.0 / 3.0);
    g = hue_to_rgb(p, q, h);
    b = hue_to_rgb(p, q, h - 1.0 / 3.0);

    return Color(r, g, b);
}


#endif // COLOR_H_5F0626917B33E5F7

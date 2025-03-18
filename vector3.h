#ifndef VECTOR3_H_8C0E1EA1CE507ED2
#define VECTOR3_H_8C0E1EA1CE507ED2

#include <cmath>
#include <vector>
#include "fputils.h"


struct Vector3
{
    double x;
    double y;
    double z;

    Vector3() = delete;
    Vector3(double x, double y, double z): x(x), y(y), z(z) {}
    Vector3(const Vector3& v): x(v.x), y(v.y), z(v.z) {}

    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }

    Vector3 operator-() const { return Vector3(-x, -y, -z); }

    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator-(const Vector3& v) const { return *this + -v; }
    Vector3& operator+=(const Vector3& v) { return *this = *this + v; }
    Vector3& operator-=(const Vector3& v) { return *this = *this - v; }

    Vector3 operator*(const double s) const { return Vector3(x * s, y * s, z * s); }
    Vector3 operator/(const double s) const { return *this * (1.0 / s); }
    Vector3& operator*=(const double s) { return *this = *this * s; }
    Vector3& operator/=(const double s) { return *this = *this / s; }

    double dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vector3 cross(const Vector3& v) const { return Vector3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }

    double magnitude_squared() const { return x * x + y * y + z * z; }
    double magnitude() const { return std::sqrt(magnitude_squared()); }
    Vector3 normalized() const { return *this / this->magnitude(); }
    Vector3& normalize() { return *this /= this->magnitude(); }

    double operator[](size_t i) const { return i == 0 ? x : i == 1 ? y : i == 2 ? z : std::numeric_limits<double>::quiet_NaN(); }

    inline Vector3 reflect(const Vector3& normal) const;
    inline Vector3 refract(const Vector3& normal, double r) const;

    static Vector3 none() { return Vector3(FPUtils::NaN(), FPUtils::NaN(), FPUtils::NaN()); }

    static inline Vector3 random_direction();
};


inline Vector3 Vector3::reflect(const Vector3& normal) const
{
    return *this - normal * this->dot(normal) * 2.0;
}

inline Vector3 Vector3::refract(const Vector3& normal, double r) const
{
    const double cos_theta { -this->dot(normal) };
    const Vector3 perpendicular { (*this + normal * cos_theta) * r };
    const Vector3 parallel { normal * -std::sqrt(std::abs(1.0 - perpendicular.magnitude_squared())) };
    return perpendicular + parallel;
}


inline Vector3 Vector3::random_direction()
{
    return Vector3(FPUtils::random_normal(), FPUtils::random_normal(), FPUtils::random_normal()).normalized();
}


using Point3 = Vector3;


struct Ray
{
    Point3 origin;
    Vector3 direction;

    Ray(const Point3& o, const Vector3& d): origin(o), direction(d) {}

    Vector3 operator[](double t) const { return origin + direction * t; }
};


struct Basis
{
    Vector3 i;
    Vector3 j;
    Vector3 k;

    Basis(const Vector3& i, const Vector3& j, const Vector3& k): i(i), j(j), k(k) {}

    static Basis axes() { return Basis(Vector3(1.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0), Vector3(0.0, 0.0, 1.0)); }
};


#endif // VECTOR3_H_8C0E1EA1CE507ED2

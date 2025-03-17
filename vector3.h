#ifndef VECTOR3_H_88D6417780F96753
#define VECTOR3_H_88D6417780F96753

#include <cmath>
#include <limits>
#include <random>


inline double rand_double(double lo, double hi)
{
    static std::uniform_real_distribution<double> dist(lo, hi);
    static std::default_random_engine re;
    return dist(re);
}


struct Vector3
{
    double x, y, z;

    Vector3(double x, double y, double z): x(x), y(y), z(z) {}
    Vector3(const Vector3& v): x(v.x), y(v.y), z(v.z) {}

    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }

    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    
    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3& operator+=(const Vector3& v) { return *this = *this + v; }
    Vector3 operator-(const Vector3& v) const { return *this + -v; }

    Vector3 operator*(const double s) const { return Vector3(x * s, y * s, z * s); }
    Vector3 operator/(const double s) const { return *this * (1.0 / s); }

    Vector3 operator*(const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }
    double dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vector3 cross(const Vector3& v) const { return Vector3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }

    Vector3 reflect(const Vector3& v) const { return *this - v * this->dot(v) * 2.0; }
    Vector3 refract(const Vector3& v, double r) const
    {
        const double cos_theta { std::fmin((-(*this).dot(v)), 1.0) };
        Vector3 perpendicular { (*this + v * cos_theta) * r };
        Vector3 parallel { v * -std::sqrt(std::fabs(1.0 - perpendicular.dot(perpendicular))) };
        return perpendicular + parallel;
    }

    double magnitude() const { return std::sqrt(x * x + y * y + z * z); }
    Vector3 normal() const { return *this / this->magnitude(); }
    Vector3& normalize() { return *this = *this / this->magnitude(); }

    double operator[](size_t i) const { return i == 0 ? x : i == 1 ? y : i == 2 ? z : std::numeric_limits<double>::quiet_NaN(); }

    static Vector3 none() { return Vector3(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()); }

    static Vector3 random_unit_vector()
    {
        for (Vector3 ret(1, 1, 1); ; ret = Vector3(rand_double(-1, 1), rand_double(-1, 1), rand_double(-1, 1)))
        {
            if (ret.magnitude() <= 1)
            {
                return ret / ret.magnitude();
            }
        }
    }
};


using Point3 = Vector3;


struct Ray
{
    Point3 origin;
    Vector3 direction;

    Ray(Point3 o, Vector3 d): origin(o), direction(d) {}

    Vector3 operator[](const double t) const { return origin + direction * t; }
};


struct Basis
{
    Vector3 i;
    Vector3 j;
    Vector3 k;

    Basis(): i(Vector3(1, 0, 0)), j(Vector3(0, 1, 0)), k(Vector3(0, 0, 1)) {}
};


using Color = Vector3;


#endif // VECTOR3_H_88D6417780F96753

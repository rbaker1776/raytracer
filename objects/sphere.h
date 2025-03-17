#ifndef SPHERE_H_7C27FD98572DAB0D
#define SPHERE_H_7C27FD98572DAB0D

#include <cmath>
#include <memory>
#include "../visible.h"
#include "../vector3.h"
#include "../material.h"
#include "../bbox.h"


class Sphere: public Visible
{
private:
    Vector3 center;
    double radius;
    std::shared_ptr<Material> material;
    BBox bbox;

public:
    Sphere(const Vector3& center, double radius, std::shared_ptr<Material> mat):
        center(center), radius(radius), material(mat), bbox(
            Interval(center.x - radius, center.x + radius),
            Interval(center.y - radius, center.y + radius),
            Interval(center.z - radius, center.z + radius)
        )
    {}

    bool is_seen(const Ray& ray, HitRecord& record, Interval t_interval) const override
    {
        // a sphere with center P = { x, y, z } = { A, B, C } and radius R
        // can be defined by the equation:
        //
        //  P² == (x - A)² + (y - B)² + (z - C)² == R²
        //
        // recall that a ray is defined by O + Dt. if we sub O + Dt for P
        // in the equation of a sphere we get:
        //
        //  (O + Dt)² == R² ==> (O + Dt)² - R² == 0 ==> D²t² + 2ODt + O² - R² == 0
        //
        // this is a standard quadratic equation of form at² + bt + c == 0 where:
        //
        //  a = D²
        //  b = 2 * O * D
        //  c = O² - R²
        //
        // the roots of this quadratic, should they exist, are the points of
        // intersection between the ray and the sphere

        const Vector3 R { ray.origin - this->center };

        const double a { ray.direction.dot(ray.direction) };
        const double b { R.dot(ray.direction) * 2.0 };
        const double c { R.dot(R) - this->radius * this->radius };

        const double det { b * b - 4 * a * c };
        if (det < 0) { return false; }

        const double t { (-b - std::sqrt(det)) / (2.0 * a) };

        if (t_interval.does_include(t))
        {
            record.intersection = ray[t];
            record.normal = (record.intersection - center).normal();
            record.t = t;
            record.material = material;
            return true;
        }

        return false;
    }

    BBox bounding_box() const override { return this->bbox; }
};


#endif // SPHERE_H_7C27FD98572DAB0D

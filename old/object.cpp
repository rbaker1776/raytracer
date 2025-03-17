#include "object.h"
#include "scene.h"


static bool solve_quadratic(double a, double b, double c, double& t0, double& t1)
{
    const double det { b * b - 4 * a * c };

    if (det < 0)
    {
        return false;
    }

    t0 = -b + std::sqrt(det) / 2 / a;
    t1 = -b - std::sqrt(det) / 2 / a;

    return true;
}


bool Sphere::is_seen(const Ray& ray, Vector3& intersection) const
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

    double t0, t1;
    if (!solve_quadratic(a, b, c, t0, t1))
    {
        return false;
    }

    if (t0 >= 0 && t0 < t1)
    {
        intersection = ray[t0];
        return true;
    }
    else if (t1 >= 0)
    {
        intersection = ray[t1];
        return true;
    }

    return false;
};


bool Plane::is_seen(const Ray& ray, Vector3& intersection) const
{
    const double r_dot_n { ray.direction.dot(this->normal) };

    if (std::abs(r_dot_n) > 1e-9)
    {
        const double t { (this->p0 - ray.origin).dot(this->normal) / r_dot_n };
        if (t >= 0)
        {
            intersection = ray[t];
            return true;
        }
    }

    return false;
}

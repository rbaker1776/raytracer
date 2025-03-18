#ifndef OBJECT_H_063AB1D4F40483E7
#define OBJECT_H_063AB1D4F40483E7

#include "fputils.h"
#include "vector3.h"
#include "interval.h"
#include <cmath>


class Material;


struct HitRecord
{
    Point3 point = Point3::none();
    Vector3 normal = Vector3::none();
    double t = FPUtils::infinity();
    std::shared_ptr<Material> material = nullptr;
};


class Object
{
public:
    virtual ~Object() = default;

    virtual bool is_seen(const Ray& ray, HitRecord& record, Interval& t_bounds) const = 0;
};


class Sphere: public Object
{
private:
    Point3 center;
    double radius;
    std::shared_ptr<Material> material;

public:
    Sphere(const Point3& p, double r, std::shared_ptr<Material> mat):
        center(p), radius(r), material(mat)
    {}

    bool is_seen(const Ray& ray, HitRecord& record, Interval& t_bounds) const override
    {
        const Vector3 R { ray.origin - center };
        
        // a == 1 because ray.direction.magnitude() == 1
        const double b { 2.0 * R.dot(ray.direction) };
        const double c { R.magnitude_squared() - radius * radius };

        const double det { b * b - 4.0 * c };

        if (det < 0)
        {
            return false;
        }

        const double t { (-b - std::sqrt(det)) / 2.0 };
        
        if (!t_bounds.does_include(t))
        {
            return false;
        }

        record.point = ray[t];
        record.normal = (record.point - center).normalized();
        record.t = t;
        record.material = material;
        
        return true;
    }
};


class Plane: public Object
{
private:
    Vector3 point;
    Vector3 normal;
    std::shared_ptr<Material> material;

public:
    Plane(const Vector3& p, const Vector3& n, std::shared_ptr<Material> mat):
        point(p), normal(n), material(mat)
    {}

    bool is_seen(const Ray& ray, HitRecord& record, Interval& t_bounds) const override
    {
        const double r_dot_n { ray.direction.dot(normal) };

        if (r_dot_n < -1e-9)
        {
            const double t { (this->point - ray.origin).dot(normal) / r_dot_n };

            if (t_bounds.does_include(t))
            {
                record.point = ray[t];
                record.normal = normal;
                record.t = t;
                record.material = material;

                return true;
            }
        }

        return false;
    }
};


#endif // OBJECT_H_063AB1D4F40483E7

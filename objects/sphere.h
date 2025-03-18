#ifndef SPHERE_H_3CDE530041D66B87
#define SPHERE_H_3CDE530041D66B87

#include <cmath>


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


#endif // SPHERE_H_3CDE530041D66B87

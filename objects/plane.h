#ifndef PLANE_H_88D127A9C5675503
#define PLANE_H_88D127A9C5675503

#include "../visible.h"
#include "../vector3.h"
#include "../material.h"


class Plane: public Visible
{
private:
    Vector3 p0;     // we decide to define a plane by a point
    Vector3 normal; // and a normal vector
    std::shared_ptr<Material> material;

public:
    Plane(const Vector3& p0, const Vector3& n, std::shared_ptr<Material> mat):
        p0(p0), normal(n), material(mat)
    {}

    bool is_seen(const Ray& ray, HitRecord& record, Interval t_interval) const override
    {
        const double r_dot_n { ray.direction.dot(this->normal) };

        if (std::abs(r_dot_n) > 1e-9)
        {
            const double t { (this->p0 - ray.origin).dot(this->normal) / r_dot_n };
            if (t_interval.does_include(t))
            {
                record.intersection = ray[t];
                record.normal = normal;
                record.t = t;
                record.material = material;
                return true;
            }
        }

        return false;
    }

    BBox bounding_box() const override { return BBox::world(); }
};


#endif // PLANE_H_88D127A9C5675503

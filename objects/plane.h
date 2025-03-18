#ifndef PLANE_H_2DDF5DD94F9B00D1
#define PLANE_H_2DDF5DD94F9B00D1


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


#endif // PLANE_H_2DDF5DD94F9B00D1

#ifndef VISIBLE_H_FAC8FB4D8705B221
#define VISIBLE_H_FAC8FB4D8705B221

#include <memory>
#include <limits>
#include "vector3.h"
#include "bbox.h"


class Material;


struct HitRecord
{
    Point3 intersection = Point3::none();
    Vector3 normal = Point3::none();
    double t = -std::numeric_limits<double>::infinity();
    bool is_front = true;
    std::shared_ptr<Material> material = nullptr;
};


class Visible
{
public:
    virtual ~Visible() = default;

    virtual bool is_seen(const Ray& ray, HitRecord& record, Interval t_interval) const = 0;

    virtual BBox bounding_box() const = 0;
};


#endif // VISIBLE_H_FAC8FB4D8705B221

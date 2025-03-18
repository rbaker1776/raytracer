#ifndef OBJECT_H_063AB1D4F40483E7
#define OBJECT_H_063AB1D4F40483E7

#include "fputils.h"
#include "vector3.h"
#include "interval.h"


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


#include "objects/sphere.h"
#include "objects/plane.h"


#endif // OBJECT_H_063AB1D4F40483E7

#ifndef MATERIAL_H_B3E722D970B5DA7D
#define MATERIAL_H_B3E722D970B5DA7D

#include "vector3.h"
#include "color.h"
#include "texture.h"


class Material
{
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;

    virtual Color emit(const Point3& p) const = 0;
};


#include "materials/lambertian.h"


#endif // MATERIAL_H_B3E722D970B5DA7D

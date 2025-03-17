#ifndef MATERIAL_H_E92BCE0A290D3376
#define MATERIAL_H_E92BCE0A290D3376

#include "visible.h"


class Material
{
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;
};


#endif // MATERIAL_H_E92BCE0A290D3376

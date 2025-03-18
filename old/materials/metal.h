#ifndef METAL_H_8644A9088CE1C020
#define METAL_H_8644A9088CE1C020

#include "../material.h"
#include "../vector3.h"


class Metal: public Material
{
protected:
    Color albedo;
    double fuzz;

public:
    Metal(Color albedo, double fuzz): albedo(albedo), fuzz(Interval::clamp(fuzz, 0, 1)) {}

    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
    {
        Vector3 reflection { ray.direction.reflect(record.normal).normal() + Vector3::random_unit_vector() * fuzz };
        scattered = Ray(record.intersection, reflection.normal());
        attenuation = albedo;
        return scattered.direction.dot(record.normal) > 0;
    }
};


class Mirror: public Metal
{
public:
    Mirror(): Metal(Color(1.0, 1.0, 1.0), 0.0) {}
};


#endif // METAL_H_8644A9088CE1C020

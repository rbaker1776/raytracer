#ifndef MIRROR_H_B52C071B8EF326FA
#define MIRROR_H_B52C071B8EF326FA

#include "../material.h"


class Mirror: public Material
{
private:
    Color albedo;
    double fuzz;

public:
    Mirror(Color albedo = Color(1, 1, 1), double fuzz = 0):
        albedo(albedo), fuzz(Interval::clamp(fuzz, 0, 1))
    {}

    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
    {
        Vector3 reflection { ray.direction.reflect(record.normal).normal() + Vector3::random_unit_vector() * fuzz };
        scattered = Ray(record.intersection, reflection.normal());
        attenuation = albedo;
        return scattered.direction.dot(record.normal) > 0;
    }
};


#endif // MIRROR_H_B52C071B8EF326FA

#ifndef LAMBERTIAN_H_9010D12703E732E2
#define LAMBERTIAN_H_9010D12703E732E2

#include "../material.h"
#include "../vector3.h"


class Lambertian: public Material
{
private:
    Color albedo;

public:
    Lambertian(const Color& c): albedo(c) {}

    bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
    {
        Vector3 direction(0, 0, 0);

        while (direction.magnitude() < 1e-12)
        {
            direction = record.normal + Vector3::random_unit_vector();
        }

        scattered = Ray(record.intersection, direction);
        attenuation = albedo;
        return true;
    }
};


#endif // LAMBERTIAN_H_9010D12703E732E2

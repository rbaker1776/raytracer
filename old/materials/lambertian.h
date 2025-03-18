#ifndef LAMBERTIAN_H_9010D12703E732E2
#define LAMBERTIAN_H_9010D12703E732E2

#include "../material.h"
#include "../texture.h"
#include "../textures/solid.h"
#include "../vector3.h"


class Lambertian: public Material
{
protected:
    std::shared_ptr<Texture> texture;

public:
    Lambertian(std::shared_ptr<Texture> tex): texture(tex) {}
    Lambertian(const Color& albedo): texture(std::make_shared<Solid>(albedo)) {}

    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
    {
        Vector3 direction(0, 0, 0);

        while (direction.magnitude() < 1e-12)
        {
            direction = record.normal + Vector3::random_unit_vector();
        }

        scattered = Ray(record.intersection, direction);
        attenuation = texture->color(record.intersection);
        return true;
    }
};


#endif // LAMBERTIAN_H_9010D12703E732E2

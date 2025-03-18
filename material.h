#ifndef MATERIAL_H_B3E722D970B5DA7D
#define MATERIAL_H_B3E722D970B5DA7D

#include "vector3.h"
#include "color.h"
#include "texture.h"
#include "interval.h"


class Material
{
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;

    virtual Color emit(const Point3& p) const = 0;
};


class Lambertian: public Material
{
private:
    std::shared_ptr<Texture> texture;

public:
    Lambertian(std::shared_ptr<Texture> tex): texture(tex) {}
    Lambertian(const Color& c): texture(std::make_shared<Solid>(c)) {}

    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
    {
        Vector3 direction { (record.normal + Vector3::random_direction()).normalized() };

        scattered = Ray(record.point, direction);
        attenuation = texture->color(record.point);

        return true;
    }

    virtual Color emit(const Point3& p) const override { return Color(0.0, 0.0, 0.0); }
};


class Metal: public Material
{
private:
    Color albedo;
    double fuzz;

public:
    Metal(Color albedo, double fuzz): albedo(albedo), fuzz(Interval::clamp(fuzz, 0.0, 1.0)) {}

    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
    {
        const Vector3 reflection { ray.direction.reflect(record.normal).normalized() + Vector3::random_direction() * fuzz };

        scattered = Ray(record.point, reflection.normalized());
        attenuation = albedo;
        
        return scattered.direction.dot(record.normal) > 0;
    }

    virtual Color emit(const Point3& p) const override { return Color(0.0, 0.0, 0.0); }
};


class Mirror: public Metal
{
public:
    Mirror(): Metal(Color(1.0, 1.0, 1.0), 0.0) {}
};


#endif // MATERIAL_H_B3E722D970B5DA7D

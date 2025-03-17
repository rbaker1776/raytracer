#ifndef DIELECTRIC_H_D0568E11FF3B2F30
#define DIELECTRIC_H_D0568E11FF3B2F30

#include "../material.h"
#include "../vector3.h"


class Dielectric: public Material
{
private: 
    double refraction_idx;

    static double reflectance(double cosine, double ri)
    {
        double r0 { (1.0 - ri) / (1.0 + ri) };
        r0 *= r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }

public:
    Dielectric(double refraction_idx): refraction_idx(refraction_idx) {}

    bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
    {
        attenuation = Color(1.0, 1.0, 1.0);
        const double ri { record.is_front ? ( 1.0 / refraction_idx ) : ( refraction_idx ) };

        const double cos_theta { std::fmin(-(ray.direction.dot(record.normal)), 1.0) };
        const double sin_theta { std::sqrt(1.0 - cos_theta * cos_theta) };

        bool can_refract { ri * sin_theta <= 1.0 };
        Vector3 direction { Vector3::none() };

        if (!can_refract || reflectance(cos_theta, ri) > rand_double(0, 1))
        {
            direction = ray.direction.reflect(record.normal);
        }
        else
        {
            direction = ray.direction.refract(record.normal, ri);
        }

        scattered = Ray(record.intersection, direction);
        return true;
    }
};


#endif // DIELECTRIC_H_D0568E11FF3B2F30

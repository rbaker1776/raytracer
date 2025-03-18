#ifndef LAMBERTIAN_H_AABE71950DF0678D
#define LAMBERTIAN_H_AABE71950DF0678D


class Lambertian: public Material
{
private:
    std::shared_ptr<Texture> texture;

public:
    Lambertian(std::shared_ptr<Texture> tex): texture(tex) {}
    Lambertian(const Color& c): texture(std::make_shared<Solid>(c)) {}

    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override
    {
        Vector3 direction(0, 0, 0);
        while (direction.magnitude() < 1e-12)
        {
            direction = record.normal + Vector3::random_direction();
        }

        scattered = Ray(record.point, direction);
        attenuation = texture->color(record.point);

        return true;
    }

    virtual Color emit(const Point3& p) const override { return Color(0.0, 0.0, 0.0); }
};


#endif // LAMBERTIAN_H_AABE71950DF0678D

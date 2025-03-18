#ifndef LIGHT_H_3C13CA04F598B624
#define LIGHT_H_3C13CA04F598B624

#include "../material.h"
#include "../texture.h"
#include "../textures/solid.h"


class Light: public Material
{
private:
    std::shared_ptr<Texture> texture;
    double intensity;

public:
    Light(std::shared_ptr<Texture> tex, double intensity): texture(tex), intensity(intensity) {}
    Light(const Color& c, double intensity): texture(std::make_shared<Solid>(c)), intensity(intensity) {}

    Color emitted (const Point3& p) const override { return texture->color(p) * intensity; }
};


#endif // LIGHT_H_3C13CA04F598B624

#ifndef LIGHT_H_3C13CA04F598B624
#define LIGHT_H_3C13CA04F598B624

#include "../material.h"
#include "../texture.h"
#include "../textures/solid.h"


class Light: public Material
{
private:
    std::shared_ptr<Texture> texture;

public:
    Light(std::shared_ptr<Texture> tex): texture(tex) {}
    Light(const Color& c): texture(std::make_shared<Solid>(c)) {}

    Color emitted (const Point3& p) const override { return texture->color(p); }
};


#endif // LIGHT_H_3C13CA04F598B624

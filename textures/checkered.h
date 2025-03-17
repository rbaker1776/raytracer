#ifndef CHECKERED_H_C5D5686A61D440E2
#define CHECKERED_H_C5D5686A61D440E2

#include "../texture.h"
#include "../vector3.h"
#include "solid.h"
#include <algorithm>


class Checkered: public Texture
{
private:
    std::shared_ptr<Texture> tex_a;
    std::shared_ptr<Texture> tex_b;

public:
    Checkered(std::shared_ptr<Texture> a, std::shared_ptr<Texture> b): tex_a(a), tex_b(b) {}
    Checkered(const Color& a, const Color& b): tex_a(std::make_shared<Solid>(a)), tex_b(std::make_shared<Solid>(b)) {}

    Color color(const Point3& p) const override
    {
        int64_t sum { static_cast<long long>(std::floor(p.x) + std::floor(p.y) + std::floor(p.z)) };
        return sum & 1 ? tex_a->color(p) : tex_b->color(p);
    }
};


#endif // CHECKERED_H_C5D5686A61D440E2

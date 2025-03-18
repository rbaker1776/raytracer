#ifndef TEXTURE_H_B98F82082DE9C978
#define TEXTURE_H_B98F82082DE9C978

#include "vector3.h"
#include "color.h"


class Texture
{
public:
    virtual ~Texture() = default;

    virtual Color color(const Point3& p) const = 0;
};


#include "textures/solid.h"


#endif // TEXTURE_H_B98F82082DE9C978

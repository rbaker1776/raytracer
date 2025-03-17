#ifndef TEXTURE_H_6E0B8552D14C85D2
#define TEXTURE_H_6E0B8552D14C85D2

#include "vector3.h"


class Texture
{
public:
    virtual ~Texture() = default;

    virtual Color color(const Point3& p) const = 0;
};


#endif // TEXTURE_H_6E0B8552D14C85D2

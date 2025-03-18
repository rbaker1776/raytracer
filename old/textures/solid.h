#ifndef SOLID_H_BFB89FF4CD8E08BE
#define SOLID_H_BFB89FF4CD8E08BE

#include "../texture.h"
#include "../vector3.h"


class Solid: public Texture
{
private:
    Color albedo;

public:
    Solid(const Color& albedo): albedo(albedo) {}

    Color color(const Point3& p) const override { return albedo; }
};


#endif // SOLID_H_BFB89FF4CD8E08BE

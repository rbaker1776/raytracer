#ifndef SOLID_H_E74EB97B612000F3
#define SOLID_H_E74EB97B612000F3


class Solid: public Texture
{
private:
    Color albedo;

public:
    Solid(const Color& albedo): albedo(albedo) {}

    Color color(const Point3& p) const override { return albedo; }
};


#endif // SOLID_H_E74EB97B612000F3

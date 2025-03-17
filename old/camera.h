#ifndef CAMERA_H_57D950BC05276D57
#define CAMERA_H_57D950BC05276D57

#include "vector3.h"
#include "visible.h"


class Camera
{
private:
    Point3 position;
    Vector3 direction;

    Point3 pixel_naught;

    void init(size_t width, size_t height);

    double get_ray(const double px, const double py) const;

public:
    void render(const Visible& scene, const Image& image);
};


#endif // CAMERA_H_57D950BC05276D57

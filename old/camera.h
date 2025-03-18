#ifndef CAMERA_H_411588EF308B2950
#define CAMERA_H_411588EF308B2950

#include <cstdint>
#include "vector3.h"
#include "image.h"
#include "scene.h"


class Camera
{
private:
    Point3  position  = Point3 (0, 0, 0); // camera's position { x, y, z }
    Vector3 direction = Vector3(1, 0, 0); // camera's orientation { x, y, z }
                                          //
    size_t x_res = 1920;                  // width of image in pixels 
    size_t y_res = 1080;                  // height of image in pixels
    double fov = 75.0;                    // vertical FOV in degrees
                                          //
    double focal_length = 5;              // distance to the plane of focus
    double blur_angle = 5e-2;             // variation of ray angles through a pixel
                                          //
    Basis basis = Basis();                // camera's frame basis vectors { i, j, k }
    Vector3 pixel_dj = Vector3(0, 0, 0);  // step 1 pixel in the direction of basis.j
    Vector3 pixel_dk = Vector3(0, 0, 0);  // step 1 pixel in the direction of basis.k
    Point3  pixel_00 = Point3 (0, 0, 0);  // coords of the first pixel { x, y, z }
                                          //
    int n_rays_per_pixel = 256;           // # of rays we shoot at each pixel

    Ray make_ray(size_t j, size_t k) const;
    Color ray_color(const Ray& ray, int depth, const Scene& scene) const;

    void update_viewport();

    Color background(const Ray& ray) const
    {
        const double inclination { 0.5 * (ray.direction.normal().y + 1.0) };
        return Color(1.0, 1.0, 1.0) * (1.0 - inclination) + Color(0.5, 0.7, 1.0) * inclination;
    }

public:
    Camera() { update_viewport(); }

    void move_to(const Point3& point) { position = point; update_viewport(); }
    void turn_to(const Point3& point) { direction = (point - position).normal(); update_viewport(); }
    void orient(const Vector3& dir) { direction = dir; update_viewport(); }

    void set_resolution(size_t width, size_t height) { x_res = width; y_res = height; update_viewport(); }
    void set_fov(double angle) { fov = angle; update_viewport(); }

    Image render(const Scene& scene) const;
};


#endif // CAMERA_H_411588EF308B2950

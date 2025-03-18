#ifndef CAMERA_H_6D580543283E0B13
#define CAMERA_H_6D580543283E0B13

#include "vector3.h"
#include "image.h"
#include "scene.h"
#include <cstdint>


class Camera
{
private:
    Point3  position  = Point3 (0.0, 0.0, 0.0); // position { x, y, z }
    Vector3 direction = Vector3(1.0, 0.0, 0.0); // orientation { x, y, z }
                                                //
    size_t x_res = 1920;                        // image width in pixels
    size_t y_res = 1080;                        // image height in pixels
    double vfov = 75.0;                         // vertical FOV in degrees
                                                //
    Basis basis = Basis::axes();                // frame basis vectors { i, j, k }
    Vector3 pixel_dj = Vector3::none();         // step 1 pixel in the direction basis.j
    Vector3 pixel_dk = Vector3::none();         // step 1 pixel in the direction basis.k
    Point3  pixel_00 = Point3::none();          // coords of the first pixel { x, y, z }
                                                //
    int n_rays_per_pixel = 256;                 // # of rays we shoot at each pixel

public:
    Camera() { update_viewport(); }

    void move_to(const Point3& p) { position = p; update_viewport(); }
    void look_at(const Point3& p) { direction = (p - position).normalized(); update_viewport(); }
    void orient(const Vector3& d) { direction = d.normalized(); update_viewport(); }

    void set_resolution(size_t w, size_t h) { x_res = w; y_res = h; update_viewport(); }
    void set_vfov(double vfov) { this->vfov = vfov; update_viewport(); }

    Image render(const Scene& scene) const;

private:
    void update_viewport();

    Ray make_ray(size_t j_pix, size_t k_pix) const;

    Color trace(const Ray& ray, int depth, const Scene& scene) const;

    Color background(const Ray& ray) const;
};


#endif // CAMERA_H_6D580543283E0B13

#include "camera.h"
#include <numbers>


// initializes the camera's viewport varibales to render an image of a
// given size in pixels
void Camera::init(const size_t width, const size_t height)
{
    this->aspect_ratio = static_cast<double>(width) / static_cast<double>(height);

    const double h { std::tan(this->fov * std::numbers::pi / 360.0) };
    const double vp_width  { 2.0 * h * this->focus };
    const double vp_height { vp_width / this->aspect_ratio };

    this->basis.i = this->direction.normal();
    this->basis.j = this->basis.i.cross(Vector3(0, 1, 0)).normal();
    this->basis.k = this->basis.i.cross(this->basis.j);
}

Ray Camera::get_ray(const double px, const double py) const
{
    
}


void Camera::render(const Visible& scene, Image& image)
{
    for (size_t i = 0; i < image.height(); ++i)
    for (size_t j = 0; j < image.width();  ++j)
    {
        Ray r { this->get_ray(static_cast<double>(i) / image.height(), static_cast<double>(j) / image.width()) };
        Color c { this->shoot_ray(r, scene) };
    }
}

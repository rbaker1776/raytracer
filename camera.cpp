#include "camera.h"
#include <numbers>
#include <limits>
#include "visible.h"
#include "material.h"


void Camera::update_viewport()
{
    this->basis.i = this->direction.normal();
    this->basis.j = basis.i.cross(Vector3(0, 1, 0)).normal();
    this->basis.k = basis.i.cross(basis.j).normal();

    const double viewport_width  { 2.0 * std::tan(fov * std::numbers::pi / 360.0) * focal_length };
    const double viewport_height { viewport_width * static_cast<double>(y_res) / static_cast<double>(x_res) };

    this->pixel_dj = basis.j * viewport_width  / static_cast<double>(x_res);
    this->pixel_dk = basis.k * viewport_height / static_cast<double>(y_res);
    this->pixel_00 = position + basis.i * focal_length - basis.j * viewport_width / 2.0 - basis.k * viewport_height / 2.0;
}


Ray Camera::make_ray(size_t j, size_t k) const
{
    const Vector3 direction { (pixel_00 + pixel_dj * j + pixel_dk * k - position).normal() };
    return Ray(position, (direction + Vector3::random_unit_vector() * std::tan(blur_angle * std::numbers::pi / 180.0)).normal());
}


Color Camera::ray_color(const Ray& ray, int depth, const Scene& scene) const
{
    if (depth < 0) { return Color(0, 0, 0); }

    HitRecord record;

    if (scene.is_seen(ray, record, Interval(1e-6, 1e6)))
    {
        Ray scattered(Vector3(0, 0, 0), Vector3(0, 0, 0));
        Color attenuation(0, 0, 0);
        if (record.material->scatter(ray, record, attenuation, scattered))
        {
            return attenuation * this->ray_color(scattered, depth - 1, scene);
        }
    }

    double a { 0.5 * (ray.direction.normal().y + 1.0) };
    return Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;
}


Image Camera::render(const Scene& scene) const
{
    Image image(x_res, y_res);
    const double n_rays { 10 };

    HitRecord record {};

    for (size_t i = 0; i < y_res; ++i)
    for (size_t j = 0; j < x_res; ++j)
    {
        for (int k = 0; k < n_rays; ++k)
        {
            const Ray ray { this->make_ray(j, i) };
            Color pixel_color { ray_color(ray, 10, scene) };
            image[i][j] = image[i][j] + pixel_color / n_rays;
        }
    }

    return image;
}

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

    if (!scene.is_seen(ray, record, Interval(1e-6, 1e6)))
    {
        return this->background(ray);
    }

    Ray scattered(Vector3::none(), Vector3::none());
    Color attenuation(0, 0, 0);
    Color emitted_color { record.material->emitted(record.intersection) };

    if (!record.material->scatter(ray, record, attenuation, scattered))
    {
        return emitted_color;
    }

    Color scattered_color { attenuation * ray_color(scattered, depth - 1, scene) };
    return scattered_color + emitted_color;
}


Image Camera::render(const Scene& scene) const
{
    Image image(x_res, y_res);
    HitRecord record {};

    for (size_t i = 0; i < y_res; ++i)
    for (size_t j = 0; j < x_res; ++j)
    {
        Color pixel_color(0, 0, 0);
        for (int k = 0; k < n_rays_per_pixel; ++k)
        { 
            const Ray ray { this->make_ray(j, i) };
            pixel_color += ray_color(ray, 10, scene) / n_rays_per_pixel;
        }
        image[i][j] = pixel_color;
    }

    return image;
}

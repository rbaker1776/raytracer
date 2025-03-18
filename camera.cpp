#include "camera.h"
#include "object.h"
#include "material.h"
#include <numbers>


void Camera::update_viewport()
{
    this->basis.i = direction.normalized();
    this->basis.j = basis.i.cross(Vector3(0.0, 1.0, 0.0)).normalized();
    this->basis.k = basis.i.cross(basis.j).normalized();

    const double viewport_height { 2.0 * std::tan(vfov * std::numbers::pi / 360.0) };
    const double viewport_width { viewport_height * static_cast<double>(x_res) / static_cast<double>(y_res) };

    this->pixel_dj = basis.j * viewport_width  / static_cast<double>(x_res);
    this->pixel_dk = basis.k * viewport_height / static_cast<double>(y_res);
    this->pixel_00 = position + basis.i - basis.j * viewport_width / 2.0 - basis.k * viewport_height / 2.0;
}


Ray Camera::make_ray(size_t j_pix, size_t k_pix) const
{
    const Vector3 direction { (pixel_00 + pixel_dj * j_pix + pixel_dk * k_pix - position).normalized() };
    return Ray(position, direction);
}


Color Camera::trace(const Ray& ray, int depth, const Scene& scene) const
{
    if (depth < 0)
    {
        return Color(0.0, 0.0, 0.0);
    }

    HitRecord record;
    Interval t_bounds(1e-6, 1e6);

    if (!scene.is_seen(ray, record, t_bounds))
    {
        return this->background(ray);
    }

    Ray scattered(Vector3::none(), Vector3::none());
    Color attenuation(0.0, 0.0, 0.0);
    Color emitted_color { record.material->emit(record.point) };

    if (!record.material->scatter(ray, record, attenuation, scattered))
    {
        return emitted_color;
    }

    Color scattered_color { attenuation * trace(scattered, depth - 1, scene) };
    return scattered_color + emitted_color;
}


Image Camera::render(const Scene& scene) const
{
    Image image(x_res, y_res);
    HitRecord record {};

    for (size_t k = 0; k < y_res; ++k)
    for (size_t j = 0; j < x_res; ++j)
    {
        Color pixel_color(0.0, 0.0, 0.0);

        for (int i = 0; i < n_rays_per_pixel; ++i)
        { 
            const Ray ray { make_ray(j, k) };
            pixel_color += trace(ray, 10, scene) / n_rays_per_pixel;
        }

        image[k][j] = pixel_color;
    }

    return image;
}


Color Camera::background(const Ray& ray) const
{
    const double inclination { 0.5 * (ray.direction.normalized().y + 1.5) };
    return Color(1.0, 1.0, 1.0) * (1.0 - inclination) + Color(0.5, 0.7, 1.0) * inclination;
}

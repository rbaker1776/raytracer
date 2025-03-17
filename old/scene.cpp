#include "scene.h"
#include <cmath>
#include <numbers>


void Scene::render(const Camera& camera, Image& image) const
{
    // define a basis from our camera's direction
    const Basis basis(camera.direction);
    const double M { std::tan(camera.fov * std::numbers::pi / 360) };

    for (size_t i = 0; i < image.height(); ++i)
    for (size_t j = 0; j < image.width(); ++j)
    {
        // for each pixel, we shoot a ray from the camera's position in a certain
        // direction D calculated from the camera's basis. 
        //
        //  basis.i == camera.direction is normal to the plane onto which we project.
        //  basis.j has a y component of 0, can be thought of as pointing to the camera's left
        //  basis.k can be thought of as pointing above the camera
        //
        // to construct D, we sum basis.i with multiples of basis.j and basis.k corresponding
        // to the current pixel. the maximum multiple of basis.j ought to be the tangent of
        // the camera's FOV. the maximum multiple of basis.k is the maximum multiple of
        // basis.j divided by the image's aspect ratio. hence, D is given by:
        //
        //  D = basis.i + basis.j * tan(FOV) * [-1, 1] + basis.k * tan(FOV) * [-1, 1] / aspect
        //
        // where the factor within [-1, 1] is given by the current pixel's spot in the image.

        Ray ray(camera.position, Vector3(basis.i + basis.j * M * (2.0 * (static_cast<double>(j) / image.width() - 0.5)) + basis.k * M * (-2.0 * (static_cast<double>(i) / image.height() - 0.5)) / image.aspect_ratio()));
        Vector3 intersection(0, 0, 0); 

        for (const auto& obj: this->objects)
        {
            if (obj->is_seen(ray, intersection))
            {
                image[i][j] = { uint8_t(int(intersection.x * 128)), uint8_t(int(intersection.y * 128)), uint8_t(int(intersection.z * 128)) };
            }
        }
    }
}

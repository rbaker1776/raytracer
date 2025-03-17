#include <iostream>
#include "vector3.h"
#include "camera.h"
#include "scene.h"
#include "objects/sphere.h"
#include "objects/plane.h"
#include "material.h"
#include "materials/lambertian.h"
#include "materials/dielectric.h"
#include "image.h"


int main()
{
    Camera camera;
    camera.move_to(Point3(0, 1, 0));
    camera.orient(Vector3(1, 0, 0));
    camera.set_resolution(512, 512);

    Scene scene;
    scene.add(std::make_shared<Sphere>(Vector3(5, 2, 0), 1, std::make_shared<Lambertian>(Color(1, 0, 1))));
    scene.add(std::make_shared<Plane>(Vector3(0, 0, 0), Vector3(0, 1, 0), std::make_shared<Dielectric>(0)));

    Image image { camera.render(scene) };
    image.write_to_ppm("out.ppm");
}

#include <iostream>
#include <chrono>
#include "vector3.h"
#include "camera.h"
#include "scene.h"
#include "objects/sphere.h"
#include "objects/plane.h"
#include "material.h"
#include "materials/lambertian.h"
#include "materials/dielectric.h"
#include "materials/metal.h"
#include "materials/light.h"
#include "textures/checkered.h"
#include "image.h"


int main()
{
    Camera camera;
    camera.move_to(Point3(0, 2, 0));
    camera.orient(Vector3(1, 0, 0));
    camera.set_resolution(1920, 1280);

    Scene scene;
    scene.add(std::make_shared<Plane>(Vector3(0, 0, 0), Vector3(0, 1, 0), std::make_shared<Lambertian>(std::make_shared<Checkered>(Color(0.1, 0.1, 0.2), Color(0.05, 0.05, 0.1)))));
    scene.add(std::make_shared<Sphere>(Vector3(15, 5, 5), 5, std::make_shared<Mirror>()));
    scene.add(std::make_shared<Sphere>(Vector3(15, 5, -5), 5, std::make_shared<Mirror>()));
    scene.add(std::make_shared<Sphere>(Vector3(7, 1, 0), 1, std::make_shared<Lambertian>(Color(1, 0.4, 0))));
    scene.add(std::make_shared<Sphere>(Vector3(7, 1, 2.1), 1, std::make_shared<Lambertian>(Color(0, 1, 0.4))));
    scene.add(std::make_shared<Sphere>(Vector3(7, 1, -2.1), 1, std::make_shared<Lambertian>(Color(0.4, 0, 1))));
    scene.add(std::make_shared<Sphere>(Vector3(9, 6, 0), 0.5, std::make_shared<Mirror>()));

    using namespace std::chrono;
    auto start = steady_clock::now();

    Image image { camera.render(scene) };

    auto end = steady_clock::now();
    long long duration { duration_cast<milliseconds>(end - start).count() };
    std::cout << "rendered in " << duration << " milliseconds" << std::endl;

    image.write_to_ppm("out.ppm");
}

#include <iostream>
#include <chrono>
#include "scene.h"
#include "camera.h"
#include "image.h"
#include "material.h"
#include "texture.h"


int main()
{
    Scene scene;

    Camera camera;
    camera.move_to(Point3(0.0, 1.0, 0.0));
    camera.orient(Vector3(1, 0, 0));
    camera.set_resolution(512, 512);
    
    scene.add(std::make_shared<Plane>(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0), std::make_shared<Lambertian>(std::make_shared<Checkered>(Color(0.10, 0.10, 0.20), Color(0.05, 0.05, 0.10)))));
    scene.add(std::make_shared<Sphere>(Vector3(5.0, 1.0, 0.0), 1.0, std::make_shared<Lambertian>(Color(1.0, 0.25, 0.0))));
    //scene.add(std::make_shared<Sphere>(Vector3(5.0, 1.0, 0.0), 1.0, std::make_shared<Mirror>()));
    scene.add(std::make_shared<Sphere>(Vector3(5.0, 1.0, -2.0), 1.0, std::make_shared<Lambertian>(Color(0.1, 0.25, 0.8))));
    scene.add(std::make_shared<Sphere>(Vector3(5.0, 1.0, 2.0), 1.0, std::make_shared<Lambertian>(Color(0.2, 0.95, 0.2))));

    using namespace std::chrono;
    auto start = steady_clock::now();

    Image image { camera.render(scene) };

    auto end = steady_clock::now();
    long long duration { duration_cast<milliseconds>(end - start).count() };
    std::cout << "rendered in " << duration << " milliseconds" << std::endl;

    image.write_to_ppm("out.ppm");
}

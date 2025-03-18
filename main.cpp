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
    scene.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, std::make_shared<Lambertian>(Color(1.0, 0.25, 0.0))));    
    scene.add(std::make_shared<Plane>(Point3(0, 0, 0), Vector3(0, 1.0, 0), std::make_shared<Lambertian>(Color(0.1, 0.1, 0.2))));    

    Camera camera;
    camera.move_to(Point3(-6, 1, 0));
    camera.orient(Vector3(1, 0, 0));
    camera.set_resolution(512, 512);

    using namespace std::chrono;
    auto start = steady_clock::now();

    Image image { camera.render(scene) };

    auto end = steady_clock::now();
    long long duration { duration_cast<milliseconds>(end - start).count() };
    std::cout << "rendered in " << duration << " milliseconds" << std::endl;

    image.write_to_ppm("out.ppm");
}

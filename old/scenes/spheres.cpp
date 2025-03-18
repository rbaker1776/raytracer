#include <iostream>
#include <chrono>

#include "../vector3.h"
#include "../camera.h"
#include "../scene.h"
#include "../objects/sphere.h"
#include "../objects/plane.h"
#include "../material.h"
#include "../materials/lambertian.h"
#include "../materials/metal.h"
#include "../textures/checkered.h"
#include "../image.h"


int main()
{
    Camera camera;
    camera.move_to(Point3(-20, 6, 0));
    camera.turn_to(Vector3(0, 0, 0));
    camera.set_resolution(1024, 1024);
    camera.set_fov(45);

    Scene scene;
    scene.add(std::make_shared<Plane>(Vector3(0, 0, 0), Vector3(0, 1, 0), std::make_shared<Lambertian>(std::make_shared<Checkered>(Color(0.1, 0.1, 0.2), Color(0.05, 0.05, 0.1)))));
    scene.add(std::make_shared<Sphere>(Vector3(10, 5, 0), 5, std::make_shared<Mirror>()));

    for (int i = 0; i <= 10; ++i)
    for (int j = 0; j <= 10; ++j)
    {
        double u { static_cast<double>(i) / 10 };
        double v { static_cast<double>(j) / 10 };
        Color c { Color::HSLtoRGB(Color((u + v) / 2, 1.0, 0.5)) };

        scene.add(std::make_shared<Sphere>(Vector3(5 - i, 0.45, 5 - j), 0.45, std::make_shared<Lambertian>(Color(c))));
    }

    using namespace std::chrono;
    auto start { steady_clock::now() };

    Image image { camera.render(scene) };
    
    auto end { steady_clock::now() };
    long long duration { duration_cast<milliseconds>(end - start).count() };

    std::cout << "rendered in " << duration << " milliseconds" << std::endl;
    image.write_to_ppm("out.ppm");
}

#include <iostream>
#include <cmath>
#include <chrono>
#include "image.h"
#include "object.h"
#include "scene.h"


int main()
{
    using namespace std::chrono;

    auto start { steady_clock::now() };

    Image image(4096, 4096);
    std::unique_ptr<Sphere> s { std::make_unique<Sphere>(Vector3(5, 5, 1), 0.5) };
    std::unique_ptr<Sphere> t { std::make_unique<Sphere>(Vector3(3, 1, -1), 0.2) };
    std::unique_ptr<Plane> p { std::make_unique<Plane>(Vector3(0, 0, 0), Vector3(0, 1, 0)) };
    Scene scene;
    scene.add(std::move(p));
    scene.add(std::move(s));
    Camera camera( { 0, 2, 0}, {1, 0, 0}, 90 );

    scene.render(camera, image);

    image.write_to_ppm("out.ppm");

    auto end { steady_clock::now() };
    const double duration { static_cast<double>(duration_cast<milliseconds>(end - start).count()) };

    std::cout << "finished in " << duration << " milliseconds" << std::endl;
}

#ifndef SCENE_H_5678C1EA9D6E5570
#define SCENE_H_5678C1EA9D6E5570

#include <vector>
#include <memory>


class Scene
{
private:
    std::vector<std::shared_ptr<Visible>> objects;

public:
    Scene() = default;
    Scene(std::shared_ptr<Visible> obj): objects(std::vector<std::shared_ptr<Visible>>(1, obj)) {}

    void clear() { this->objects.clear(); }
    void add(std::shared_ptr<Visible> obj) { this->objects.push_back(obj); }
}


#endif // SCENE_H_5678C1EA9D6E5570

struct Camera
{
    Vector3 direction;
    double fov; // FOV in degrees
    
    Camera(Vector3 pos, Vector3 dir, double fov): position(pos), direction(dir), fov(fov) {}
};


class Scene
{
private:
    std::vector<std::unique_ptr<Visible>> objects;

public:
    Scene() = default;
    
    void add(std::unique_ptr<Visible> obj) { this->objects.push_back(std::move(obj)); }

    void render(const Camera& camera, Image& image) const;
};


#endif // SCENE_H_CB511A8445040000

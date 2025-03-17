#ifndef MATERIAL_H_B5E900516FEDD830
#define MATERIAL_H_B5E900516FEDD830


class Material
{
public:
    virtaul ~Material() = default;

    virtual Ray scatter(const Ray& ray);
};


#endif // MATERIAL_H_B5E900516FEDD830

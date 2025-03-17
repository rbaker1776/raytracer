#ifndef OBJECT_H_CB511A8445040000
#define OBJECT_H_CB511A8445040000

#include "vector3.h"


struct Ray;


class Visible
{
public:
    virtual ~Visible() = default;

    virtual bool is_seen(const Ray& ray, Vector3& intersection) const = 0;
};


class Sphere: public Visible
{
private:
    Vector3 center;
    double radius;

public:
    Sphere(const Vector3& center, double radius): center(center), radius(radius) {}

    bool is_seen(const Ray& ray, Vector3& intersection) const;
};




#endif // OBJECT_H_CB511A8445040000

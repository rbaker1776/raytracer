#ifndef SCENE_H_12B57E44482118EC
#define SCENE_H_12B57E44482118EC

#include <vector>
#include <memory>
#include <limits>
#include "visible.h"
#include "vector3.h"
#include "bbox.h"


class Scene: public Visible
{
public:
    std::vector<std::shared_ptr<Visible>> objects;

    Scene() = default;

    void clear() { objects.clear(); }
    void add(std::shared_ptr<Visible> obj) { objects.push_back(obj); }

    bool is_seen(const Ray& ray, HitRecord& record, Interval t_interval) const override
    {
        HitRecord tmp_record {};
        bool seen { false };
        double nearest { std::numeric_limits<double>::max() };

        for (const std::shared_ptr<Visible>& obj: objects)
        {
            if (obj->is_seen(ray, tmp_record, Interval(0, nearest)))
            {
                seen = true;
                record = tmp_record;
                nearest = record.t;
            }
        }

        return seen;
    }

    BBox bounding_box() const override
    {
        BBox box { BBox::empty() };
        for (const std::shared_ptr<Visible>& obj: objects)
        {
            box.grow_to_include(obj->bounding_box());
        }
        return box;
    }
};


#endif // SCENE_H_12B57E44482118EC

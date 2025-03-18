#ifndef SCENE_H_E7EDF35D1CA274E7
#define SCENE_H_E7EDF35D1CA274E7

#include <vector>
#include <memory>
#include "object.h"


class Scene: public Object
{
private:
    std::vector<std::shared_ptr<Object>> objects;

public:
    Scene() = default;

    void clear() { objects.clear(); }
    void add(std::shared_ptr<Object> obj) { objects.push_back(obj); }

    bool is_seen(const Ray& ray, HitRecord& record, Interval& t_bounds) const override
    {
        HitRecord temp_record;
        bool seen { false };

        for (const std::shared_ptr<Object>& obj: objects)
        {
            if (obj->is_seen(ray, temp_record, t_bounds))
            {
                seen = true;
                record = temp_record;
                t_bounds.set_max(record.t);
            }
        }

        return seen;
    }
};


#endif // SCENE_H_E7EDF35D1CA274E7

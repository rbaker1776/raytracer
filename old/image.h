#ifndef IMAGE_H_CB511A8445040000
#define IMAGE_H_CB511A8445040000

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include "vector3.h"
#include "bbox.h"


class Image
{
private:
    std::vector<std::vector<Color>> data;

    int scale(double d) const
    {
        d = std::sqrt(Interval::clamp(d, 0, 0.999));
        return static_cast<int>(d * 255);
    }

public:
    Image(size_t width = 0, size_t height = 0):
        data(std::vector<std::vector<Color>>(height, std::vector<Color>(width, Color(0, 0, 0))))
    {}

    size_t width() const { return this->data[0].size(); }
    size_t height() const { return this->data.size(); }
    double aspect_ratio() const { return static_cast<double>(width()) / height(); }

    std::vector<Color>& operator[](size_t i) { return this->data[i]; } 
    const std::vector<Color>& operator[](size_t i) const { return this->data[i]; } 

    void write_to_ppm(const std::string& filepath) const
    {
        std::ofstream f(filepath, std::ios::trunc);

        f << "P3" << '\n';
        f << this->width() << ' ' << this->height() << '\n';
        f << 255 << '\n';

        for (const std::vector<Color>& row: this->data)
        {
            for (Color p: row)
            {
                f << scale(p.x) << ' ' << scale(p.y) << ' ' << scale(p.z) << ' ';
            }
            f << '\n';
        }

        f.close();
    }
};


#endif // IMAGE_H_CB511A8445040000

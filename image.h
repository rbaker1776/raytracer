#ifndef IMAGE_H_CB511A8445040000
#define IMAGE_H_CB511A8445040000

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include "color.h"


class Image
{
private:
    std::vector<std::vector<Color>> data;

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
                const Vector3 rgb { p.gamma_correct() * 255 };
                f << static_cast<int>(rgb.x) << ' ' << static_cast<int>(rgb.y) << ' ' << static_cast<int>(rgb.z) << ' ';
            }
            f << '\n';
        }

        f.close();
    }

    static Image from_ppm(const std::string& filepath)
    {
        Image img {};
        std::ifstream f(filepath);

        std::string token {};
        size_t width, height;

        f >> token >> width >> height;

        img.data = std::vector<std::vector<Color>>(height, std::vector<Color>(width, Color(0, 0, 0)));

        f >> token;

        for (int i = 0; i < height; ++i)
        for (int j = 0; j < width;  ++j)
        {
            f >> img.data[i][j].x >> img.data[i][j].y >> img.data[i][j].z;
            img.data[i][j] = Color(img.data[i][j] / 255).gamma_uncorrect();
        }

        f.close();
        return img;
    }
};


#endif // IMAGE_H_CB511A8445040000

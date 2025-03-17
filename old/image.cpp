#include <fstream>
#include "image.h"


void Image::write_to_ppm(const std::string& filepath) const
{
    std::ofstream f(filepath, std::ios::trunc);

    f << "P3" << '\n';
    f << this->width() << ' ' << this->height() << '\n';
    f << 255 << '\n';

    for (const std::vector<Pixel>& row: this->data)
    {
        for (Pixel p: row)
        {
            f << int(p.r) << ' ' << int(p.g) << ' ' << int(p.b) << ' ';
        }
        f << '\n';
    }

    f.close();
}

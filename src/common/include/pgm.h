#pragma once

#include "headers.h"
#include "types.h"

#include <vector>
#include <string>

namespace pgm {

    image::Headers get_headers(std::string);
    image::Headers create_headers(image::BitMap data);
    image::Headers create_headers(image::ColorBitMap data);

    image::BitMap get_data(std::string filename, image::Headers headers);
    image::ColorBitMap get_ppm_data(std::string filename, image::Headers headers);

    int write(struct image::Headers headers, image::BitMap data, std::string path);
    int write(image::BitMap data, std::string path);
    int write_ppm(struct image::Headers headers, image::ColorBitMap data, std::string path);

} // pgm


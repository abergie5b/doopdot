#pragma once

#include "../../common/include/types.h"

#include <vector>

namespace algos {

    size_t circular_idx(int x, size_t limit);
    size_t reflect_idx(int x, size_t limit);
    image::BitMap convolve(image::BitMap data, image::Kernel kernel);
    image::ColorBitMap convolve_rgb(image::ColorBitMap data, image::Kernel kernel);
    image::Kernel get_gaussian_kernel(size_t K);

} // algos


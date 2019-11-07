#pragma once

#include "../../common/include/types.h"

#include <vector>

namespace algos {

    image::BitMap median_filter(image::BitMap data, size_t K);
    image::BitMap laplace_filter(image::BitMap data, size_t K);
    image::BitMap maximum_filter(image::BitMap data, size_t K);
    image::BitMap minimum_filter(image::BitMap data, size_t K);
    image::BitMap sobel(image::BitMap data);
    image::ColorBitMap sobel(image::ColorBitMap data);
    image::BitMap prewitt(image::BitMap data);
    image::ColorBitMap prewitt_rgb(image::ColorBitMap data);

} // algos


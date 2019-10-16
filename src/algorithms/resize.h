
#pragma once
#include <vector>
#include "../common/types.h"

namespace algos {

    double lerp(double x1, double x2, double t);
    image::BitMap nearest_neighbors(image::BitMap data, int width, int height);
    image::BitMap bilinear_interp(image::BitMap data, int width, int height);
    image::BitMap bicubic_interp(image::BitMap data);
    image::BitMap resize_with_resample(image::BitMap data, float alpha);

} // algos


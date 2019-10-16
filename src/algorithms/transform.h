
#pragma once
#include <vector>
#include "../common/types.h"

namespace algos {

    image::BitMap rotate90(image::BitMap img);
    image::BitMap negative(image::BitMap img);

    image::ColorBitMap invert_channel(int channel, image::ColorBitMap data);

} // algos


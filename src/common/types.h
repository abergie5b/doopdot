#pragma once

#include <cstdint>
#include <vector>
#include <map>

namespace image
{
    enum Channel
    {
        RED,
        BLUE,
        GREEN,
        ALPHA
    };

    enum ImageType
    {
        JPEG,
        PGM,
        PPM
    };

    // 8-bit representation of pixel values
    typedef uint8_t Pixel;

    // For greyscale images
    typedef std::vector<std::vector<Pixel>> BitMap;

    // For RGB and other multi-channel images
    typedef std::vector<std::vector<std::vector<Pixel>>> ColorBitMap;

    // For histograms
    typedef std::map<Pixel, Pixel> PixelMap;

} //image


#pragma once

#include <string>
#include <vector>
#include <map>

#include "headers.h"
#include "types.h"

namespace image
{

class Image
{
public:
    std::string filename;
    ImageType image_type;
    struct Headers headers;
    image::BitMap data;
    image::ColorBitMap rgb_data;
    Image(std::string, std::string type);
    void print_headers();
    int writeas(std::string path, std::string type);
    std::map<image::Pixel, unsigned int> get_histogram();
    void resize(size_t width, size_t height, std::string method);
    void negative();
    void rotate90();
    void equalize_contrast();
    void convolve(image::Kernel kernel);
    void filter(std::string type);
    void sobel();
    void prewitt();
    void reset_headers();
    virtual ~Image();
private:
};
} // image


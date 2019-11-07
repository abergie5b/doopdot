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
    // 
    std::string filename;
    ImageType image_type;

    // Headers
    struct Headers headers;
    void print_headers();

    // Pixel Data
    image::BitMap data;
    image::ColorBitMap rgb_data;

    // Constructor
    Image(std::string, std::string type);

    // Image Manipulation
    void resize(size_t width, size_t height, std::string method);
    void negative();
    void rotate90();
    void equalize_contrast();
    void convolve(image::Kernel kernel);
    void filter(std::string type);
    void sobel();
    void prewitt();
    void gaussian_smoothing();
    void to_grayscale();

    // Meta
    std::map<image::Pixel, unsigned int> get_histogram();

    // Save
    int writeas(std::string path, std::string type);
    
    // Destroy
    virtual ~Image();
private:
    //
    bool is_rgb;
    
    // Headers
    void reset_headers();

};

} // image


#pragma once

#include <string>
#include <vector>

namespace image
{
    struct Headers
    {
        std::string filename;
        std::string version;
        std::vector<std::string> comments;
        size_t width;
        size_t height;
        size_t pixel_size;
        unsigned int max_grayscale;
    };

} // image


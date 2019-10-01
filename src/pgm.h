#pragma once
#include <vector>
#include <string>

namespace pgm {

    class NetPbmImage
    {
    public:
        const char* filename;
        struct headers
        {
            std::string magic_number;
            std::string text;
            int width;
            int height;
            int max_grayscale;
        } headers;
        std::vector<int> data;
        NetPbmImage(const char* filename);
    private:
        void read(const char* _filename);
    };
} // pgm

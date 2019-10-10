#pragma once
#include <vector>
#include <string>

namespace pgm {
    struct Headers
    {
        std::string title;
        std::string magic_number;
        std::string text;
        int width;
        int height;
        int max_grayscale;
    };

    class NetPbmImage
    {
    public:
        const char* filename;
        struct Headers headers;
        const char* delim = " ";
        std::vector<std::vector<int>> data;
        NetPbmImage(const char* filename);
    private:
        void read(const char* _filename);
        void set_headers(std::vector<std::string> values);
    };

    int write(NetPbmImage img, const char* path);
    int write(struct Headers headers, std::vector<std::vector<int>> data, const char* path);
    int write(std::string magic_number, std::string text, std::vector<std::vector<int>> data, const char* path);

} // pgm


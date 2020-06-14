#pragma once

#include "../../common/include/types.h"

#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <fstream>
#include <iostream>

namespace algos {

    struct sorted_by_keys
    {
        // TODO
        bool operator()(std::string a, std::string b) const
        {
            char* context = nullptr;
            std::string token = strtok_s(const_cast<char*>(a.c_str()), "-", &context);
            unsigned int aval = std::stoi(token, NULL, 10);
            token = strtok_s(const_cast<char*>(b.c_str()), "-", &context);
            unsigned int bval = std::stoi(token, NULL, 10);
            return aval < bval;
        }
    };
    std::map<image::Pixel, unsigned int> get_histogram(image::BitMap data);
    void display(std::string title, std::map<std::string, unsigned int, sorted_by_keys> hist, int max_grayscale);
    std::map<std::string, unsigned int, sorted_by_keys> groupby(std::map<image::Pixel, unsigned int> hist, int magnitude);
    image::BitMap equalize_contrast(image::BitMap img);

} // algos


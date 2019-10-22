#include "convolution.h"

#include <iostream>

namespace algos {

    size_t circular(int x, size_t limit)
    {
        if (x < 0)
            return limit + x;
        else if (x >= limit)
            return x - limit;
        return x;
    }

    size_t reflect(int x, size_t limit)
    {
        if (x < 0)
            return -x - 1;
        else if (x >= limit)
            return 2*limit - x - 1;
        return x;
    }

    image::BitMap convolve(image::BitMap data, image::Kernel kernel)
    {
        image::BitMap out;
        size_t height = data.size();
        size_t width = data[0].size();

        size_t k_height = kernel.size();
        size_t k_width = kernel[0].size();
        if (k_height != k_width)
        {
            return out;
        }
        int K = k_height/2;

        for (int y=0; y<height; y++)
        {
            std::vector<image::Pixel> row;
            for (int x=0; x<width; x++)
            {
                double sum = 0;
                for (int ky=-K; ky<=K; ky++)
                {
                    for (int kx=-K; kx<=K; kx++)
                    {
                        size_t _y = circular(y + ky, height);
                        size_t _x = circular(x + kx, width);
                        sum += (double)data[_y][_x] * kernel[ky + K][kx + K];
                    }
                }
                row.push_back(sum);
            }
            out.push_back(row);
        }
        return out;
    };

} // algos


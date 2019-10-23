#include "filter.h"
#include "convolution.h"

#include <algorithm>

namespace algos
{
    image::BitMap median_filter(image::BitMap data, size_t size)
    {
        image::BitMap out;
        size_t height = data.size();
        size_t width = data[0].size();

        int K = size/2;

        for (int y=0; y<height; y++)
        {
            std::vector<image::Pixel> row;
            for (int x=0; x<width; x++)
            {
                std::vector<image::Pixel> arr;
                for (int ky=-K; ky<=K; ky++)
                {
                    for (int kx=-K; kx<=K; kx++)
                    {
                        size_t _y = circular_idx(y + ky, height);
                        size_t _x = circular_idx(x + kx, width);
                        arr.push_back(data[_y][_x]);
                    }
                }
                std::sort(arr.begin(), arr.end());
                if (arr.size() % 2 == 0)
                    row.push_back((arr[K/2] + arr[K/2-1]) / 2);
                row.push_back(arr[K]);
            }
            out.push_back(row);
        }
        return out;
    }

    image::BitMap maximum_filter(image::BitMap data, size_t size)
    {
        image::BitMap out;
        size_t height = data.size();
        size_t width = data[0].size();

        int K = size/2;

        for (int y=0; y<height; y++)
        {
            std::vector<image::Pixel> row;
            for (int x=0; x<width; x++)
            {
                image::Pixel maximum = 0;
                for (int ky=-K; ky<=K; ky++)
                {
                    for (int kx=-K; kx<=K; kx++)
                    {
                        size_t _y = circular_idx(y + ky, height);
                        size_t _x = circular_idx(x + kx, width);
                        image::Pixel val = data[_y][_x];
                        if (maximum < val)
                            maximum = val;
                    }
                }
                row.push_back(maximum);
            }
            out.push_back(row);
        }
        return out;
    }


    image::BitMap minimum_filter(image::BitMap data, size_t size)
    {
        image::BitMap out;
        size_t height = data.size();
        size_t width = data[0].size();

        int K = size/2;

        for (int y=0; y<height; y++)
        {
            std::vector<image::Pixel> row;
            for (int x=0; x<width; x++)
            {
                image::Pixel minimum = 0;
                for (int ky=-K; ky<=K; ky++)
                {
                    for (int kx=-K; kx<=K; kx++)
                    {
                        size_t _y = circular_idx(y + ky, height);
                        size_t _x = circular_idx(x + kx, width);
                        image::Pixel val = data[_y][_x];
                        if (minimum > val)
                            minimum = val;
                    }
                }
                row.push_back(minimum);
            }
            out.push_back(row);
        }
        return out;
    }

    image::BitMap sobel(image::BitMap data)
    {
        image::Kernel hfilter = {
            {-1.0, 0.0, 1.0},
            {-2.0, 0.0, 2.0},
            {-1.0, 0.0, 1.0}
        };
        image::Kernel vfilter = {
            {-1.0, -2.0, -1.0},
            {0.0, 0.0, 0.0},
            {1.0, 2.0, 1.0}
        };
        image::BitMap out = convolve(data, hfilter);
        out = convolve(out, vfilter);
        return out;
    }

    image::ColorBitMap sobel(image::ColorBitMap data)
    {
        image::Kernel hfilter = {
            {-1.0, 0.0, 1.0},
            {-2.0, 0.0, 2.0},
            {-1.0, 0.0, 1.0}
        };
        image::Kernel vfilter = {
            {-1.0, -2.0, -1.0},
            {0.0, 0.0, 0.0},
            {1.0, 2.0, 1.0}
        };
        image::ColorBitMap out = convolve_rgb(data, hfilter);
        out = convolve_rgb(out, vfilter);
        return out;
    }

    image::BitMap prewitt(image::BitMap data)
    {
        image::Kernel hfilter = {
            {1.0, 0.0, -1.0},
            {1.0, 0.0, -1.0},
            {1.0, 0.0, -1.0}
        };
        image::Kernel vfilter = {
            {1.0, 1.0, 1.0},
            {0.0, 0.0, 0.0},
            {-1.0, -1.0, -1.0}
        };
        image::BitMap out = convolve(data, hfilter);
        out = convolve(out, vfilter);
        return out;
    }

    image::ColorBitMap prewitt_rgb(image::ColorBitMap data)
    {
        image::Kernel hfilter = {
            {1.0, 0.0, -1.0},
            {1.0, 0.0, -1.0},
            {1.0, 0.0, -1.0}
        };
        image::Kernel vfilter = {
            {1.0, 1.0, 1.0},
            {0.0, 0.0, 0.0},
            {-1.0, -1.0, -1.0}
        };
        image::ColorBitMap out = convolve_rgb(data, hfilter);
        out = convolve_rgb(out, vfilter);
        return out;
    }

    image::BitMap laplace_filter(image::BitMap data, size_t size)
    {
        image::BitMap out;
        return out;
    }


} //algos


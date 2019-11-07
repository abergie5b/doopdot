#include "include/convolution.h"

#include <iostream>
#include <math.h>

namespace algos {

    double gaussian(double x, double mu, double sigma)
    {
        const double a = (x - mu) / sigma;
        return std::exp(-0.5 * a * a);
    }

    image::Kernel get_gaussian_kernel(size_t K)
    {
        double sigma = K/2;
        double sum = 0;
        size_t height = 2*K + 1;
        size_t width = 2*K + 1;
        image::Kernel out;
        for (int y=0; y<height; y++)
        {
            std::vector<double> row;
            for (int x=0; x<width; x++)
            {
                double val = gaussian(y, K, sigma) * gaussian(x, K, sigma);
                row.push_back(val);
                sum += val;
            }
            out.push_back(row);
        }

        // Normalize
        for (int y=0; y<height; y++)
        {
            for (int x=0; x<width; x++)
            {
                out[y][x] /= sum;
            }
        }
        return out;
    }

    size_t circular_idx(int x, size_t limit)
    {
        if (x < 0)
            return limit + x;
        else if (x >= limit)
            return x - limit;
        return x;
    }

    size_t reflect_idx(int x, size_t limit)
    {
        if (x < 0)
            return -x - 1;
        else if (x >= limit)
            return 2*limit - x - 1;
        return x;
    }

    image::ColorBitMap convolve_rgb(image::ColorBitMap data, image::Kernel kernel)
    {
        image::ColorBitMap out;
        size_t height = data.size();
        size_t width = data[0].size();

        size_t k_height = kernel.size();
        size_t k_width = kernel[0].size();
        if (k_height != k_width)
        {
            return out;
        }
        int K = k_height/2;

        // RGB 
        size_t channels = 3;

        for (int y=0; y<height; y++)
        {
            std::vector<std::vector<image::Pixel>> row;
            for (int x=0; x<width; x++)
            {
                std::vector<image::Pixel> channel;
                for (int c=0; c<channels; c++)
                {
                    double sum = 0;
                    for (int ky=-K; ky<=K; ky++)
                    {
                        for (int kx=-K; kx<=K; kx++)
                        {
                            size_t _y = circular_idx(y + ky, height);
                            size_t _x = circular_idx(x + kx, width);
                            sum += (double)data[_y][_x][c] * kernel[ky + K][kx + K];
                        }
                    }
                    sum = sum > 255 ? 255 : sum < 0 ? 0 : sum;
                    channel.push_back(sum);
                }
                row.push_back(channel);
            }
            out.push_back(row);
        }
        return out;
    };

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
                        size_t _y = circular_idx(y + ky, height);
                        size_t _x = circular_idx(x + kx, width);
                        sum += (double)data[_y][_x] * kernel[ky + K][kx + K];
                    }
                }
                sum = sum > 255 ? 255 : sum < 0 ? 0 : sum;
                row.push_back(sum);
            }
            out.push_back(row);
        }
        return out;
    };

} // algos


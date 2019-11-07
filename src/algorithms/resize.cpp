#include "include/resize.h"

#include <math.h>
#include <iostream>

namespace algos {

    double lerp(double x1, double x2, double t)
    {
        return x1 + (x2 - x1) * t;
    }

    image::BitMap nearest_neighbors(image::BitMap data, int width, int height)
    {
        size_t h = data.size();
        size_t w = data[0].size();

        float vscale = (h - 1) / (float)height;
        float hscale = (w - 1) / (float)width;

        size_t x, y;
        image::BitMap img_out;

        for (int y=0; y<height; y++)
        {
            if (x > width)
            {
                x = 0;
                y++;
            }
            std::vector<image::Pixel> row;
            for (int x=0; x<width; x++)
            {
                float gx = x * hscale;
                float gy = y * vscale;

                unsigned int gxi = int(gx);
                unsigned int gyi = int(gy);

                uint8_t value = data[gyi][gxi];
                row.push_back(value);
            }
            img_out.push_back(row);
        }

        return img_out;
    }

    image::BitMap bilinear_interp(image::BitMap data, int width, int height)
    {
        size_t h = data.size();
        size_t w = data[0].size();

        float vscale = (h - 1) / (float)height;
        float hscale = (w - 1) / (float)width;

        size_t x, y;
        image::BitMap img_out;

        for (int y=0; y<width; y++)
        {
            if (x > width)
            {
                x = 0;
                y++;
            }
            std::vector<image::Pixel> row;
            for (int x=0; x<height; x++)
            {
                float gx = x * hscale;
                float gy = y * vscale;

                int gxi = (int)gx;
                int gyi = (int)gy;

                uint8_t x1 = data[gy][gx];
                uint8_t y1 = data[gy+1][gx];
                uint8_t x2 = data[gy][gx+1];
                uint8_t y2 = data[gy+1][gx+1];

                float xratio = gx - gxi;
                float yratio = gy - gyi;

                uint8_t x1lerp = lerp(x1, x2, xratio);
                uint8_t x2lerp = lerp(y1, y2, xratio);
                uint8_t ylerp = lerp(x1lerp, x2lerp, yratio);

                row.push_back(ylerp);
            }
            img_out.push_back(row);
        }
        return img_out;
    }

    image::BitMap bicubic_interp(image::BitMap data)
    {
        image::BitMap img_out;
        return img_out;
    }

    image::BitMap resize_with_resample(image::BitMap data, float alpha)
    {
        
        size_t h = data.size();
        size_t w = data[0].size();

        int height = (int)h * alpha;
        int width = (int)w * alpha;

        float vscale = (h - 1) / (float)height;
        float hscale = (w - 1) / (float)width;

        size_t x, y;
        image::BitMap img_out;

        for (int y=0; y<height; y++)
        {
            if (x > width)
            {
                x = 0;
                y++;
            }
            std::vector<image::Pixel> row;
            for (int x=0; x<width; x++)
            {
                float gx = x * hscale;
                float gy = y * vscale;

                unsigned int gxi = int(gx);
                unsigned int gyi = int(gy);

                uint8_t value = data[gyi][gxi];
                row.push_back(value);
            }
            img_out.push_back(row);
        }

        return img_out;
    }

} // algos


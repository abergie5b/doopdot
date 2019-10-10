#include "resize.h"
#include <math.h>
#include <iostream>

namespace algos {

    double lerp(double x1, double x2, double t)
    {
        return x1 + (x2 - x1) * t;
    }

    std::vector<std::vector<int>> nearest_neighbors(std::vector<std::vector<int>> data, int width, int height)
    {
        int h = data.size();
        int w = data[0].size();

        float vscale = (h - 1) / (float)height;
        float hscale = (w - 1) / (float)width;

        int x, y;
        std::vector<std::vector<int>> img_out;

        for (int y=0; y<height; y++)
        {
            if (x > width)
            {
                x = 0;
                y++;
            }
            std::vector<int> row;
            for (int x=0; x<width; x++)
            {
                float gx = x * hscale;
                float gy = y * vscale;

                int gxi = int(gx);
                int gyi = int(gy);

                int value = data[gyi][gxi];
                row.push_back(value);
            }
            img_out.push_back(row);
        }

        return img_out;
    }

    std::vector<std::vector<int>> bilinear_interp(std::vector<std::vector<int>> data, int width, int height)
    {
        int h = data.size();
        int w = data[0].size();

        float vscale = (h - 1) / (float)height;
        float hscale = (w - 1) / (float)width;

        int x, y;
        std::vector<std::vector<int>> img_out;

        for (int y=0; y<width; y++)
        {
            if (x > width)
            {
                x = 0;
                y++;
            }
            std::vector<int> row;
            for (int x=0; x<height; x++)
            {
                float gx = x * hscale;
                float gy = y * vscale;

                int gxi = (int)gx;
                int gyi = (int)gy;

                uint32_t x1 = data[gy][gx];
                uint32_t y1 = data[gy+1][gx];
                uint32_t x2 = data[gy][gx+1];
                uint32_t y2 = data[gy+1][gx+1];

                float xratio = gx - gxi;
                float yratio = gy - gyi;

                uint32_t x1lerp = lerp(x1, x2, xratio);
                uint32_t x2lerp = lerp(y1, y2, xratio);
                uint32_t ylerp = lerp(x1lerp, x2lerp, yratio);

                row.push_back(ylerp);
            }
            img_out.push_back(row);
        }
        return img_out;
    }

    std::vector<std::vector<int>> bicubic_interp(std::vector<std::vector<int>> data)
    {
        std::vector<std::vector<int>> img_out;
        return img_out;
    }

    std::vector<std::vector<int>> resize_with_resample(std::vector<std::vector<int>> data, float alpha)
    {
        
        int h = data.size();
        int w = data[0].size();

        int height = (int)h * alpha;
        int width = (int)w * alpha;

        float vscale = (h - 1) / (float)height;
        float hscale = (w - 1) / (float)width;

        int x, y;
        std::vector<std::vector<int>> img_out;

        for (int y=0; y<height; y++)
        {
            if (x > width)
            {
                x = 0;
                y++;
            }
            std::vector<int> row;
            for (int x=0; x<width; x++)
            {
                float gx = x * hscale;
                float gy = y * vscale;

                int gxi = int(gx);
                int gyi = int(gy);

                int value = data[gyi][gxi];
                row.push_back(value);
            }
            img_out.push_back(row);
        }

        return img_out;
    }

} // algos


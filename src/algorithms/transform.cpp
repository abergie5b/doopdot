#include "include/transform.h"

namespace algos {

    image::BitMap convert_to_grayscale(image::ColorBitMap data)
    {
        size_t height = data.size();
        size_t width = data[0].size();
        size_t channels = 3; // RGB

        image::BitMap _data;
        for (int y=0; y<height; y++)
        {
            std::vector<image::Pixel> row;
            for (int x=0; x<width; x++)
            {
                size_t sum = 0;
                for (int c=0; c<channels; c++)
                {
                    sum += data[y][x][c];
                }
                float average = (float)sum / channels;
                average = average > 255 ? 255 : average;
                row.push_back(average);
            }
            _data.push_back(row);
        }
        return _data;
    }

    image::ColorBitMap invert_channel(int channel, image::ColorBitMap data)
    {
        size_t height = data.size();
        size_t width = data[0].size();
        size_t channels = 3; // RGB
        
        image::ColorBitMap _data = data;
        for (int y=0; y<height; y++)
        {
            for (int x=0; x<width; x++)
            {
                for (int c=0; c<channels; c++)
                {
                    if (channel == c)
                        _data[y][x][c] = 255 - _data[y][x][c];
                }
            }
        }
        return _data;
    }

    image::BitMap rotate90(image::BitMap img)
    {
        int height = img.size();
        int width = img[0].size();
        image::BitMap img_out;
        for (int x=0; x<width; x++)
        {
            std::vector<image::Pixel> row;
            for (int y=0; y<height; y++)
            {
                row.push_back( img[y][x] );
            }
            img_out.push_back(row);
        }
        return img_out;
    }

    image::BitMap negative(image::BitMap img)
    {
        int max_greyscale = 0;
        for (auto& v : img)
        {
            for (auto& p : v)
            {
                if (p > max_greyscale)
                    max_greyscale = p;
            }
        }
        int h = img.size();
        int w = img[0].size();

        image::BitMap img_out;
        for (int y=0; y<h; y++)
        {
            std::vector<image::Pixel> row;
            for (int x=0; x<w; x++)
            {
                uint8_t value = max_greyscale - img[y][x];
                row.push_back(value);
            }
            img_out.push_back(row);
        }
        return img_out;
    }

} //algos

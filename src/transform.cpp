#include "transform.h"

namespace algos {

    std::vector<std::vector<int>> negative(std::vector<std::vector<int>> img)
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

        std::vector<std::vector<int>> img_out;
        for (int y=0; y<h; y++)
        {
            std::vector<int> row;
            for (int x=0; x<w; x++)
            {
                row.push_back( max_greyscale - img[y][x] );
            }
            img_out.push_back(row);
        }
        return img_out;
    }

} //algos

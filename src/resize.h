
#pragma once
#include <vector>

namespace algos {

    double lerp(double x1, double x2, double t);
    std::vector<std::vector<int>> nearest_neighbors(std::vector<std::vector<int>> data, int width, int height);
    std::vector<std::vector<int>> bilinear_interp(std::vector<std::vector<int>> data, int width, int height);
    std::vector<std::vector<int>> bicubic_interp(std::vector<std::vector<int>> data);
    std::vector<std::vector<int>> resize_with_resample(std::vector<std::vector<int>> data, float alpha);

} // algos


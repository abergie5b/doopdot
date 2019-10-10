
#pragma once
#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <fstream>
#include <iostream>

namespace hist {

    struct sorted_by_keys
    {
        // TODO
        bool operator()(std::string a, std::string b) const
        {
            std::string token = strtok(const_cast<char*>(a.c_str()), "-");
            int aval = std::stoi(token, NULL, 10);
            token = strtok(const_cast<char*>(b.c_str()), "-");
            int bval = std::stoi(token, NULL, 10);
            return aval < bval;
        }
    };
    std::map<int, int> get_histogram(std::vector<std::vector<int>> data);
    void display(std::string title, std::map<std::string, int, sorted_by_keys> hist, int max_grayscale);
    std::map<std::string, int, sorted_by_keys> groupby(std::map<int, int> hist, int magnitude);

} // hist

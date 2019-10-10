#include "histogram.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <fstream>

namespace hist {

    struct sorted_by_keys SortedByKeys;

    std::map<std::string, int, sorted_by_keys> groupby(std::map<int, int> hist, int magnitude)
    {
        int count = 0;
        int first = 0;
        int second = 0;
        std::map<std::string, int, sorted_by_keys> out;
        for (auto const& it : hist)
        {
            if (count >= magnitude) 
            {
                int key = (int)first / magnitude;
                int value = (int)second / magnitude;

                std::string start_label = std::to_string(it.first-magnitude);
                std::string end_label = std::to_string(it.first);
                std::string label = start_label + "-" + end_label;
                out[label] = value;

                first = 0;
                second = 0;
                count = 0;
            }
            first += it.first;
            second += it.second;
            count++;
        }
        return out;
    }

    std::map<int, int> get_histogram(std::vector<std::vector<int>> data)
    {
        int height = data.size();
        int width = data[0].size();

        std::map<int, int> hist;
        for (auto& r : data)
        {
            for (auto& p : r)
            {
                if (hist.find(p) != hist.end())
                    hist[p]++;
                else
                    hist[p] = 1;
            }
        }
        return hist;
    }

    void display(std::string title, std::map<std::string, int, sorted_by_keys> hist, int max_grayscale)
    {
        int max_count = 0;
        int xlabel_length = 0;
        int xaxis_length = 0;
        int yaxis_length = 0;
        std::vector<int> values;

        for (auto const& it : hist)
        {
            if (it.second > max_count)
                max_count = it.second;
            int _xlabel_length = it.first.size();
            if (xlabel_length < _xlabel_length)
                xlabel_length = _xlabel_length;
            xaxis_length += xlabel_length + 1;
            values.push_back(it.second);
        }
        std::sort(values.begin(), values.end());

        std::string yaxis_title = "Count";
        int yaxis_title_length = yaxis_title.size();
        int y_midpoint = values[(int)values.size()/2];

        int ylabel_length = std::to_string(max_count).size();
        xaxis_length += yaxis_title_length + ylabel_length + 1;

        // Title
        for (int i=0; i<(int)xaxis_length/4; i++)
            std::cout << ' ';
        std::cout << "Histogram of " << title;
        std::cout << std::endl;

        for (int y=max_count; y>0; y--)
        {
            if (std::find(values.begin(), values.end(), y) != values.end())
            {
                // Y-Axis Title
                if (y == y_midpoint)
                    std::cout << yaxis_title;
                else
                {
                    for (int i=0; i<yaxis_title_length; i++)
                    {
                        std::cout << ' ';
                    }
                }

                // Y-Axis
                yaxis_length++;
                int y_length = std::to_string(y).size();
                std::cout << "|" << y;
                for (int i=0; i<ylabel_length-y_length; i++)
                    std::cout << " ";
                std::cout << "|";

                // Histogram
                for (auto it=hist.begin(); it!=hist.end();)
                {
                    std::cout << ' ';
                    if (it->second >= y)
                    {
                        for (int i=0; i<xlabel_length-1; i++)
                            std::cout << '_';
                    }
                    else
                    {
                        for (int i=0; i<xlabel_length-1; i++)
                            std::cout << ' ';
                    }
                    // TODO
                    if (++it != hist.end())
                        std::cout << ' ';
                }
                std::cout << "|";
                std::cout << std::endl;
            }
        }

        // X-Axis
        for (int i=0; i<yaxis_title_length; i++)
            std::cout << " ";
        std::cout << "|";
        for (int i=0; i<ylabel_length; i++)
            std::cout << "=";
        std::cout << "|";

        for (auto const& it : hist)
        {
            int x_length = it.first.size();
            for (int i=0; i<xlabel_length-x_length; i++)
                std::cout << ' '; 
            std::cout << it.first;
            std::cout << "|";
        }
        std::cout << std::endl;

        // X-Axis Title
        for (int i=0; i<(int)xaxis_length/2; i++)
            std::cout << ' ';
        std::cout << "Pixel Values";
        std::cout << std::endl;

    }

} //hist


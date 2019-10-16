#include "pgm.h"
#include <fstream>
#include <string.h>
#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <stdexcept>
#include <sstream>

namespace pgm {

    image::Headers create_headers(image::BitMap data)
    {
        struct image::Headers headers;
        headers.version= "P2";
        headers.pixel_size = 8;
        if (data.size() > 0)
        {
            headers.width = data[0].size();
            headers.height = data.size();
        }
        else
        {
            std::stringstream msg;
            msg << "No data found for write operation, exiting";
            throw std::length_error(msg.str());
        }

        unsigned short max_grayscale = 0;
        for (int y=0; y<headers.height; y++)
        {
            for (int x=0; x<headers.width; x++)
            {
                if (data[y][x] > max_grayscale)
                    max_grayscale = data[y][x];
            }
        }
        headers.max_grayscale = max_grayscale;
        return headers;
    }

    int write(image::BitMap data, std::string path)
    {
        image::Headers headers = create_headers(data);
        return write(headers, data, path);
    }

    int write(struct image::Headers headers, image::BitMap data, std::string path)
    {
        std::ofstream outfile(path);
        if (outfile.is_open())
        {
            outfile << headers.version;
            outfile << std::endl;
            if (headers.comments.size() > 0)
            {
                for (int i=0; i<headers.comments.size(); i++)
                {
                    outfile << headers.comments[i];
                    outfile << std::endl;
                }
            }
            outfile << headers.width;
            outfile << "  ";
            outfile << headers.height;
            outfile << std::endl;
            outfile << headers.max_grayscale;
            outfile << std::endl;

            // DEBUG
            std::cout << data[0].size() << "/" << data.size() << std::endl;

            size_t counter = 0;
            for (int y=0; y<headers.height; y++)
            {
                for (int x=0; x<headers.width; x++)
                {
                    outfile << (short)data[y][x];
                    outfile << "  ";
                    if (counter >= 12)
                    {
                        outfile << std::endl;
                        counter = 0;
                    }
                    counter++;
                }
            }
            outfile.close();
            struct stat s;
            if (stat(path.c_str(), &s) == -1)
                throw std::runtime_error(std::strerror(errno));
            std::cout << "Wrote " << s.st_size << " bytes to " << path << std::endl;
            return s.st_size;
        }
        std::cout << "Failed to write to " << path << std::endl;
        return -1;
    }

    image::Headers get_headers(std::string filename)
    {
        const char* delimiter = " ";
        std::ifstream infile(filename);
        std::vector<std::string> header_values;
        image::Headers _headers;

        if (infile.is_open())
        {
            std::string line;
            while (header_values.size() < 3)
            {
                std::getline(infile, line);
                if (line[0] != '#')
                    header_values.push_back(line);
                else
                    _headers.comments.push_back(line);
            }

            if (header_values.size() < 3)
            {
                std::stringstream msg;
                msg << "Error parsing headers, should be length " << 3;
                msg << ", found " << header_values.size() << ", exiting";
                throw std::length_error(msg.str());
            }
            std::string dimensions_string;
            _headers.version = header_values[0];       // PGM Version
            dimensions_string = header_values[1];          // Width  Height
             
            char* c = strtok(const_cast<char*>(dimensions_string.c_str()), delimiter);
            if (c != NULL)
            {
                _headers.width = std::stoi(c);
                c = strtok(NULL, delimiter);
                _headers.height = std::stoi(c);
            }
            else
            {
                // error
            }
            _headers.max_grayscale = std::stoi(header_values[2]);
            return _headers;
        }
    }

    image::BitMap get_data(std::string _filename, image::Headers headers)
    {
        std::ifstream infile(_filename);

        const char* delimiter = " ";
        std::vector<std::string> header_values;
        std::vector<image::Pixel> _data;
        if (infile.is_open())
        {
            std::string line;
            while (header_values.size() < 3)
            {
                std::getline(infile, line);
                if (line[0] != '#')
                    header_values.push_back(line);
            }

            std::getline(infile, line);

            char* token;
            token = strtok(const_cast<char*>(line.c_str()), delimiter);

            for (int y=0; y<headers.height*headers.width; y++)
            {
                if (token)
                {
                    uint8_t value = std::stoi(token, NULL, 10);
                    _data.push_back(value);
                    token = strtok(NULL, delimiter);
                }
                else
                {
                    std::getline(infile, line);
                    if (infile.eof())
                    {
                        break;
                    }
                    token = strtok(const_cast<char*>(line.c_str()), delimiter);
                    uint8_t value = std::stoi(token, NULL, 10);
                    _data.push_back(value);
                    token = strtok(NULL, delimiter);
                }
            }
            infile.close();
        }

        size_t i = 0;
        image::BitMap __data;
        for (int y=0; y<headers.height; y++)
        {
            std::vector<image::Pixel> row;
            for (int x=0; x<headers.width; x++)
            {
                row.push_back(_data[i]);
                i++;
            }
            __data.push_back(row);
        }
        return __data;
    }

    image::ColorBitMap get_ppm_data(std::string _filename, image::Headers headers)
    {
        std::ifstream infile(_filename);

        size_t channels = 3; // RGB
        const char* delimiter = " ";
        std::vector<std::string> header_values;
        std::vector<image::Pixel> _data;
        if (infile.is_open())
        {
            std::string line;
            while (header_values.size() < 3)
            {
                std::getline(infile, line);
                if (line[0] != '#')
                    header_values.push_back(line);
            }

            std::getline(infile, line);

            char* token;
            token = strtok(const_cast<char*>(line.c_str()), delimiter);

            for (int y=0; y<headers.height*headers.width*(channels-1); y++)
            {
                if (token)
                {
                    uint8_t value = std::stoi(token, NULL, 10);
                    _data.push_back(value);
                    token = strtok(NULL, delimiter);
                }
                else
                {
                    std::getline(infile, line);
                    if (infile.eof())
                    {
                        break;
                    }
                    token = strtok(const_cast<char*>(line.c_str()), delimiter);
                    uint8_t value = std::stoi(token, NULL, 10);
                    _data.push_back(value);
                    token = strtok(NULL, delimiter);
                }
            }
            infile.close();
        }

        size_t i = 0;
        image::ColorBitMap __data;
        for (int y=0; y<headers.height; y++)
        {
            image::BitMap row;
            for (int x=0; x<headers.width; x++)
            {
                std::vector<image::Pixel> channel;
                for (int c=0; c<channels-1; c++)
                {
                    channel.push_back(_data[i]);
                    i++;
                }
                row.push_back(channel);
            }
            __data.push_back(row);
        }
        return __data;
    }

    int write_ppm(struct image::Headers headers, image::ColorBitMap data, std::string path)
    {
        std::ofstream outfile(path);
        if (outfile.is_open())
        {
            outfile << headers.version;
            outfile << std::endl;
            if (headers.comments.size() > 0)
            {
                for (int i=0; i<headers.comments.size(); i++)
                {
                    outfile << headers.comments[i];
                    outfile << std::endl;
                }
            }
            outfile << headers.width;
            outfile << "  ";
            outfile << headers.height;
            outfile << std::endl;
            outfile << headers.max_grayscale;
            outfile << std::endl;

            // DEBUG
            std::cout << data[0].size() << "/" << data.size() << std::endl;

            size_t channels = 3; // RGB
            size_t counter = 0;
            for (int y=0; y<headers.height; y++)
            {
                for (int x=0; x<headers.width; x++)
                {
                    for (int c=0; c<channels-1; c++)
                    {
                        outfile << (short)data[y][x][c];
                        outfile << "  ";
                        if (counter >= 12)
                        {
                            outfile << std::endl;
                            counter = 0;
                        }
                        counter++;
                    }
                }
            }
            outfile.close();
            struct stat s;
            if (stat(path.c_str(), &s) == -1)
                throw std::runtime_error(std::strerror(errno));
            std::cout << "Wrote " << s.st_size << " bytes to " << path << std::endl;
            return s.st_size;
        }
        std::cout << "Failed to write to " << path << std::endl;
        return -1;
    }

} // pgm 


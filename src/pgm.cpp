#include "pgm.h"
#include <fstream>
#include <string.h>
#include <iostream>
#include <sys/stat.h>
#include <cstring>

namespace pgm {

    struct Headers headers;

    int write(struct Headers headers, std::vector<std::vector<int>> data, const char* path)
    {
        std::ofstream outfile(path);
        if (outfile.is_open())
        {
            outfile << headers.magic_number;
            outfile << std::endl;
            if (headers.text != "")
            {
                outfile << headers.text;
                outfile << std::endl;
            }
            outfile << headers.width;
            outfile << "  ";
            outfile << headers.height;
            outfile << std::endl;
            outfile << headers.max_grayscale;
            outfile << std::endl;

            std::cout << data[0].size() << "/" << data.size() << std::endl;

            unsigned int counter = 0;
            for (int y=0; y<headers.height; y++)
            {
                for (int x=0; x<headers.width; x++)
                {
                    outfile << data[y][x];
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
            if (stat(path, &s) == -1)
                throw std::runtime_error(std::strerror(errno));
            return s.st_size;
        }
        return -1;
    }

    int write(NetPbmImage img, const char* path)
    {
        return write(img.headers, img.data, path);
    }

    int write(std::string magic_number, std::string text, std::vector<std::vector<int>> data, const char* path)
    {
        struct Headers headers;
        headers.magic_number= magic_number;
        headers.text= text;
        if (data.size() > 0)
        {
            headers.width = data[0].size();
            headers.height = data.size();
        }
        else
        {
            return -1;
        }
        // TODO 
        headers.max_grayscale = 255;
        return write(headers, data, path);
    }

    NetPbmImage::NetPbmImage(const char* _filename)
    {
        filename = _filename;
        read(filename);
    }

    void NetPbmImage::read(const char* _filename)
    {
        std::ifstream infile(_filename);
        std::vector<std::string> values;

        std::vector<int> _data;
        if (infile.is_open())
        {
            std::string line;
            for (int i=0; i<4; i++)
            {
                std::getline(infile, line);
                values.push_back(line);
            }
            values.push_back(_filename);
            set_headers(values);

            char* token;

            std::getline(infile, line);
            token = strtok(const_cast<char*>(line.c_str()), delim);

            for (int y=0; y<headers.height*headers.width; y++)
            {
                if (token)
                {
                    int value = std::stoi(token, NULL, 10);
                    _data.push_back(value);
                    token = strtok(NULL, delim);
                }
                else
                {
                    std::getline(infile, line);
                    if (infile.eof())
                    {
                        break;
                    }
                    token = strtok(const_cast<char*>(line.c_str()), delim);
                    int value = std::stoi(token, NULL, 10);
                    _data.push_back(value);
                    token = strtok(NULL, delim);
                }
            }
            infile.close();
        }

        unsigned int i = 0;
        for (int y=0; y<headers.height; y++)
        {
            std::vector<int> row;
            for (int x=0; x<headers.width; x++)
            {
                row.push_back(_data[i]);
                i++;
            }
            data.push_back(row);
        }
    }

    void NetPbmImage::set_headers(std::vector<std::string> values)
    {
        std::string dimensions_string;
        headers.magic_number = values[0];       // PGM Version
        if (values[1][0] == '#')                // Optional Text Comment Line
        {
            headers.text = values[1];
            dimensions_string = values[2];      // Width  Height
        }
        else
        {
            headers.text = "";
            dimensions_string = values[1];
        }
         
        char* c = strtok(const_cast<char*>(dimensions_string.c_str()), delim);
        if (c != NULL)
        {
            headers.width = std::stoi(c);
            c = strtok(NULL, delim);
            headers.height = std::stoi(c);
        }
        else
        {
            // error
        }
        headers.max_grayscale = std::stoi(values[3]);
        headers.title = values[4];
    }

} // pgm 


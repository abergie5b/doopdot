#include "pgm.h"
#include <fstream>
#include <string.h>
#include <iostream>

namespace pgm {

    NetPbmImage::NetPbmImage(const char* _filename)
    {
        filename = _filename;
        read(filename);
    }

    void NetPbmImage::read(const char* _filename)
    {
        std::ifstream infile(_filename);
        std::vector<std::string> values;

        if (infile.is_open())
        {
            std::string line;
            // parse headers
            for (int i=0; i<4; i++)
            {
                std::getline(infile, line);
                values.push_back(line);
            }
            // read the rest of the file
            while (std::getline(infile, line))
            {
                std::cout << line << std::endl;
            }
            infile.close();
        }
        
        headers.magic_number = values[0];
        headers.text = values[1];

        const char* delim = " ";
        char* c = strtok(const_cast<char*>(values[2].c_str()), delim);
        if (c != NULL)
        {
            headers.width = std::stoi(c);
            c++;
            headers.height = std::stoi(c);
        }
        else
        {
            // error
        }
        headers.max_grayscale = std::stoi(values[3]);
    }

} // pgm 


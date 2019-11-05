#include "algorithms/resize.h"
#include "algorithms/transform.h"
#include "algorithms/convolution.h"
#include "algorithms/histogram.h"
#include "algorithms/filter.h"
#include "common/image.h"
#include "common/types.h"
#include "formats/pgm.h"

#include <iostream>

struct args
{
    std::string filename;
    std::string filetype;
    bool write = 0;
    std::string write_path;
    std::string output_format;
    bool resize = 0;
    std::string resize_method;
    int width = -1;
    int height = -1;
    bool negative = 0;
    bool histogram = 0;
    int magnitude = -1;
    bool rotate90 = 0;
    int n = -1;
    bool contrasteq = 0;
    bool convolve = 0;
    image::Kernel kernel;
    bool prewitt = 0;
    bool sobel = 0;
    bool verbose = 0;
} args;

void print_usage()
{
    std::cout << "usage: ./doopdot <file> <actions> [params] [-w <path>][-v]";
    std::cout << std::endl;
}

struct args parse_args(int argc, char* argv[])
{
    struct args arguments;
    if ( argc < 3 ) // should have at least a filename and action
    {
        print_usage();
        return arguments;
    }

    arguments.filename = argv[1];
    int idx = arguments.filename.rfind('.');

    if(idx == std::string::npos)
    {
        std::cout << "Unrecognized file extension";
        std::cout << std::endl;
        return arguments;
    }
    arguments.filetype = arguments.filename.substr(idx+1);

    std::string action = argv[2];
    for (int x=2; x<argc; x++)
    {
        std::string arg = argv[x];

        if (arg[0] == '-') // optional parameters
        {
            arg = arg.substr(1, arg.length());
            if (arg == "w") // requires filename
            {
                arguments.write = true;
                arguments.write_path = argv[x+1]; // seg fault
                arguments.output_format = arguments.filetype; // default to current format
            }
            else if (arg == "v")
                arguments.verbose = true;
            else
            {
                std::cout << "Unknown optional parameter: " << arg << std::endl;
                print_usage();
            }
        }

        else // actions
        {
            if (arg == "resize") // requires method, width, and height
            {
                arguments.resize = true;
                arguments.resize_method = argv[x+1]; // seg fault
                std::string token = strtok(const_cast<char*>(argv[x+2]), " "); // seg fault
                arguments.height = std::stoi(token, NULL, 10);
                token = strtok(const_cast<char*>(argv[x+3]), " "); // seg fault
                arguments.width = std::stoi(token, NULL, 10);
            }

            else if (arg == "negative")
                arguments.negative = true;
            else if (arg == "histogram") // requires magnitude
            {
                arguments.histogram = true;
                arguments.magnitude = std::stoi(argv[x+1], NULL, 10); // seg fault

            }
            else if (arg == "rotate90") // requires n
            {
                arguments.rotate90 = true;
                arguments.n = std::stoi(argv[x+1]); //seg fault
            }
            else if (arg == "contrasteq")
                arguments.contrasteq = true;
            else if (arg == "convolve") // requires kernel
            {
                arguments.convolve = true;
            }
            else if (arg == "prewitt") // could require threshold
            {
                arguments.prewitt = true;
            }
            else if (arg == "sobel") // could require threshold
            {
                arguments.sobel = true;
            }
        }
    }
    std::cout << arguments.filename << std::endl;
    return arguments;
}

int write_image(image::Image img, std::string path, std::string format)
{
    return img.writeas(path, format);
}

int main(int argc, char* argv[])
{
    struct args arguments = parse_args(argc, argv);
    image::Image img(arguments.filename, arguments.filetype);

    if (arguments.resize)
    {
        if (arguments.resize_method == "" || arguments.width < 0 || arguments.height < 0)
        {
            std::cout << "Resize specified without method, width, or height" << std::endl;
            print_usage();
        }
        img.resize(arguments.height, arguments.width, arguments.resize_method);
    }

    if (arguments.negative)
    {
        img.negative();
    }

    if (arguments.histogram)
    {
        if (arguments.magnitude < 0)
        {
            std::cout << "Histogram specified without magnitude" << std::endl;
            print_usage();
        }
        std::map<image::Pixel, unsigned int> pix_hist = algos::get_histogram(img.data);

        std::map<std::string, unsigned int, algos::sorted_by_keys> grouped = algos::groupby(pix_hist, arguments.magnitude);
        algos::display(img.headers.filename, grouped, img.headers.max_grayscale);
    }

    if (arguments.rotate90)
    {
        img.rotate90();
    }

    if (arguments.contrasteq)
    {
        img.equalize_contrast();
    }

    if (arguments.sobel) // detect rgb
    {
        img.sobel();
    }

    if (arguments.prewitt) // detect rgb
    {
        img.prewitt();
    }

    if (arguments.convolve) // detect rgb
    {
        // Identity 
        //image::Kernel kernel = {
        //    {0, 0, 0},
        //    {0, 1, 0},
        //    {0, 0, 0}
        //};
        
        // Sharpening
        image::Kernel kernel = {
            {0, -1, 0},
            {-1, 5, -1},
            {0, -1, 0}
        };
        
        // Edge Detector
        //image::Kernel kernel = {
        //    {-1.0, -1.0, -1.0},
        //    {-1.0, 8.0, -1.0},
        //    {-1.0, -1.0, -1.0}
        //};
        //image::Kernel kernel = algos::get_gaussian_kernel(3);
        img.convolve(kernel);
    }

    if (arguments.write)
    {
        if (arguments.write_path == "")
        {
            std::cout << "Write specified without destination" << std::endl;
            print_usage();
        }
        else
        {
            write_image(img, arguments.write_path, arguments.output_format);
        }
    }

    return 0;
}


#include "algorithms/resize.h"
#include "algorithms/transform.h"
#include "algorithms/convolution.h"
#include "algorithms/histogram.h"
#include "common/image.h"
#include "common/types.h"
#include "formats/pgm.h"

#include <iostream>

void test_ppm()
{
    image::Headers headers = pgm::get_headers("src/data/snail.ascii.ppm");
    image::ColorBitMap data = pgm::get_ppm_data("src/data/snail.ascii.ppm", headers);
    pgm::write_ppm(headers, data, "src/data/output.snail.ascii.ppm");
}

void test_image(int argc, char* argv[])
{
    if ( argc < 3 )
    {
        std::cout << "usage: ./main.o <file> <action> [parameters]";
        std::cout << std::endl;
        return;
    }

    std::string filename = argv[1];
    int idx = filename.rfind('.');

    if(idx == std::string::npos)
    {
        std::cout << "i don't recognize this  file extension";
        std::cout << std::endl;
        return;
    }
    std::string filetype = filename.substr(idx+1);

    image::Image img(filename, filetype);

    img.print_headers();
    std::string action = (std::string)argv[2];

    if (action == "resize")
    {
        std::string token = strtok(const_cast<char*>(argv[3]), " ");
        int height = std::stoi(token, NULL, 10);
        token = strtok(const_cast<char*>(argv[4]), " ");
        int width = std::stoi(token, NULL, 10);

        img.resize(height, width, argv[4]);
        img.writeas("src/data/output_zoom_bilerp.ascii.pgm", "pgm");
    }

    else if (action == "negative")
    {
        img.negative();
        img.writeas("src/data/output_negative.ascii.pgm", "pgm");
    }

    else if (action == "histogram")
    {
        std::string token = strtok(const_cast<char*>(argv[3]), " ");
        int magnitude = std::stoi(token, NULL, 10);

        std::map<image::Pixel, unsigned int> pix_hist = algos::get_histogram(img.data);

        std::map<std::string, unsigned int, algos::sorted_by_keys> grouped = algos::groupby(pix_hist, magnitude);
        algos::display(img.headers.filename, grouped, img.headers.max_grayscale);
    }

    else if (action == "rotate90")
    {
        img.rotate90();
        img.writeas("src/data/out_rotate.ascii.pgm", "pgm");
    }

    else if (action == "contrasteq")
    {
        img.equalize_contrast();
        img.writeas("src/data/out_equalize_contrast.ascii.pgm", "pgm");
    }

    else if (action == "convolve")
    {
        // Identity 
        //image::Kernel kernel = {
        //    {0, 0, 0},
        //    {0, 1, 0},
        //    {0, 0, 0}
        //};
        
        // Sharpening
        //image::Kernel kernel = {
        //    {0, -1, 0},
        //    {-1, 5, -1},
        //    {0, -1, 0}
        //};
        
        // Edge Detector
        image::Kernel kernel = {
            {-1.0, -1.0, -1.0},
            {-1.0, 8.0, -1.0},
            {-1.0, -1.0, -1.0}
        };
        image::BitMap img_out8 = algos::convolve(img.data, kernel);
        pgm::write(img_out8, "src/data/output_convolution.ascii.pgm");
    }

    else if (action == "all")
    {
        image::BitMap orig_img = img.data;

        // Zoom
        image::BitMap img_out = algos::bilinear_interp(orig_img, 1024, 1024);
        pgm::write(img_out, "src/data/output_zoom_bilerp.ascii.pgm");
            
        // Shrink
        image::BitMap img_out2 = algos::bilinear_interp(orig_img, 256, 256);
        pgm::write(img_out2, "src/data/output_shrink_bilerp.ascii.pgm");

        // Negative
        image::BitMap img_out3 = algos::negative(orig_img);
        pgm::write(img_out3, "src/data/output_negative.ascii.pgm");
        
        // Zoom with Duplication
        image::BitMap img_out4 = algos::resize_with_resample(orig_img, 2);
        pgm::write(img_out4, "src/data/output_zoom_dupe.ascii.pgm");

        // Shrink with Decimation
        image::BitMap img_out5 = algos::resize_with_resample(orig_img, 0.5);
        pgm::write(img_out5, "src/data/output_shrink_decimate.ascii.pgm");

        // Pixel Histogram
        std::map<image::Pixel, unsigned int> pix_hist = algos::get_histogram(orig_img);
        //for (auto const& it : pix_hist)
        //    std::cout << it.first << " => " << it.second << '\n';

        std::map<std::string, unsigned int, algos::sorted_by_keys> grouped = algos::groupby(pix_hist, 24);
        algos::display(img.headers.filename, grouped, img.headers.max_grayscale);
        //for (auto const& it : grouped)
        //    std::cout << it.first << " => " << it.second << '\n';

        image::BitMap img_out6 = algos::rotate90(orig_img);
        pgm::write(img_out6, "src/data/output_rotate90.ascii.pgm");

        image::BitMap img_out7 = algos::equalize_contrast(orig_img);
        pgm::write(img_out7, "src/data/output_equalize_contrast.ascii.pgm");

        image::Kernel kernel = {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
        };
        image::BitMap img_out8 = algos::convolve(orig_img, kernel);
        pgm::write(img_out8, "src/data/output_convolution.ascii.pgm");

        test_ppm();
    }
}

int main(int argc, char* argv[])
{
    test_image(argc, argv);
    //test_ppm();
    return 0;
}


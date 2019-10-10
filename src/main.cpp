#include "jpeg.h"
#include "pgm.h"
#include "resize.h"
#include "transform.h"
#include "histogram.h"

#include <fstream>
#include <iostream>

void print_image_pixels(std::vector<std::vector<int>> data)
{
    for (int y=0; y<data.size(); y++)
    {
        std::vector<int> row = data[y];
        for (int x=0; x<row.size(); x++)
        {
            std::cout << data[y][x] << ' ';
        }
        std::cout << std::endl;
    }

}

void test_jpeg(int argc, char* argv[])
{
    if ( argc < 2 )
    {
        std::cout << "No jpeg file specified\n";
    }
    try
    {
        // Constructor expects a filename to load:
        jpeg::Image img( argv[1] );

        std::cout << "\nImage height: " << img.getHeight();
        std::cout << "\nImage width : " << img.getWidth();
        // Pixel "Size" is 3 bytes for colour images (i.e. R,G, & B)
        // and 1 byte for monochrome.
        std::cout << "\nImage pixel size : " << img.getPixelSize() << " bytes";
        std::cout << std::endl;
        
        img.resize(300);
        img.save("src/data/image1.a.jpeg");

        img.resize(75);
        img.save("src/data/image1.b.jpeg");

    }
    catch( const std::exception& e )
    {
        std::cout << "Main() error handler: ";
        std::cout << e.what() << std::endl;
    }
}

void test_pgm(int argc, char* argv[])
{
    if ( argc < 3 )
    {
        std::cout << "usage: ./main.o <file> <action> [parameters]";
        std::cout << std::endl;
    }

    pgm::NetPbmImage img(argv[1]);
    std::vector<std::vector<int>> orig_img = img.data;

    std::cout << "Magic Number: " << img.headers.magic_number << std::endl;
    if (img.headers.text != "")
        std::cout << "Comment: " << img.headers.text << std::endl;
    std::cout << "Width: " << img.headers.width << std::endl;
    std::cout << "Height: " << img.headers.height << std::endl;
    std::cout << "Max Grayscale: " << img.headers.max_grayscale << std::endl;

    std::string action = (std::string)argv[2];

    if (action == "bilerp")
    {
        std::string token = strtok(const_cast<char*>(argv[3]), " ");
        int height = std::stoi(token, NULL, 10);
        token = strtok(NULL, " ");
        int width = std::stoi(token, NULL, 10);

        std::vector<std::vector<int>> img_out = algos::bilinear_interp(orig_img, height, width);
        img.data = img_out;
        img.headers.height = img_out.size();
        img.headers.width = img_out[0].size();

        const char* path = "src/data/output_zoom_bilerp.ascii.pgm";
        std::cout << "Wrote " << pgm::write(img, path) << " bytes to " << path << std::endl;
    }

    else if (action == "negative")
    {
        std::vector<std::vector<int>> img_out3 = algos::negative(orig_img);
        img.data = img_out3;
        img.headers.height = img_out3.size();
        img.headers.width = img_out3[0].size();

        const char* path3 = "src/data/output_negative.ascii.pgm";
        std::cout << "Wrote " << pgm::write(img, path3) << " bytes to " << path3 << std::endl;
    }

    else if (action == "resample")
    {
        std::string token = strtok(const_cast<char*>(argv[3]), " ");
        int alpha = std::stoi(token, NULL, 10);

        std::vector<std::vector<int>> img_out4 = algos::resize_with_resample(orig_img, alpha);
        img.data = img_out4;
        img.headers.height = img_out4.size();
        img.headers.width = img_out4[0].size();

        const char* path4 = "src/data/output_zoom_dupe.ascii.pgm";
        std::cout << "Wrote " << pgm::write(img, path4) << " bytes to " << path4 << std::endl;
    }

    else if (action == "histogram")
    {
        std::map<int, int> pix_hist = hist::get_histogram(orig_img);

        std::map<std::string, int, hist::sorted_by_keys> grouped = hist::groupby(pix_hist, 24);
        hist::display(img.headers.title, grouped, img.headers.max_grayscale);
    }

    else if (action == "all")
    {
        // Zoom
        std::vector<std::vector<int>> img_out = algos::bilinear_interp(orig_img, 1024, 1024);
        img.data = img_out;
        img.headers.height = img_out.size();
        img.headers.width = img_out[0].size();

        const char* path = "src/data/output_zoom_bilerp.ascii.pgm";
        std::cout << "Wrote " << pgm::write(img, path) << " bytes to " << path << std::endl;
            
        // Shrink
        std::vector<std::vector<int>> img_out2 = algos::bilinear_interp(orig_img, 256, 256);
        img.data = img_out2;
        img.headers.height = img_out2.size();
        img.headers.width = img_out2[0].size();

        const char* path2 = "src/data/output_shrink_bilerp.ascii.pgm";
        std::cout << "Wrote " << pgm::write(img, path2) << " bytes to " << path2 << std::endl;

        // Negative
        std::vector<std::vector<int>> img_out3 = algos::negative(orig_img);
        img.data = img_out3;
        img.headers.height = img_out3.size();
        img.headers.width = img_out3[0].size();

        const char* path3 = "src/data/output_negative.ascii.pgm";
        std::cout << "Wrote " << pgm::write(img, path3) << " bytes to " << path3 << std::endl;
        
        // Zoom with Duplication
        std::vector<std::vector<int>> img_out4 = algos::resize_with_resample(orig_img, 2);
        img.data = img_out4;
        img.headers.height = img_out4.size();
        img.headers.width = img_out4[0].size();

        const char* path4 = "src/data/output_zoom_dupe.ascii.pgm";
        std::cout << "Wrote " << pgm::write(img, path4) << " bytes to " << path4 << std::endl;

        // Shrink with Decimation
        std::vector<std::vector<int>> img_out5 = algos::resize_with_resample(orig_img, 0.5);
        img.data = img_out5;
        img.headers.height = img_out5.size();
        img.headers.width = img_out5[0].size();

        const char* path5 = "src/data/output_shrink_decimate.ascii.pgm";
        std::cout << "Wrote " << pgm::write(img, path5) << " bytes to " << path5 << std::endl;

        // Pixel Histogram
        std::map<int, int> pix_hist = hist::get_histogram(orig_img);
        //for (auto const& it : pix_hist)
        //    std::cout << it.first << " => " << it.second << '\n';

        std::map<std::string, int, hist::sorted_by_keys> grouped = hist::groupby(pix_hist, 24);
        hist::display(img.headers.title, grouped, img.headers.max_grayscale);
        //for (auto const& it : grouped)
        //    std::cout << it.first << " => " << it.second << '\n';
    }
}

int main(int argc, char* argv[])
{
    //test_jpeg(argc, argv);
    test_pgm(argc, argv);
}


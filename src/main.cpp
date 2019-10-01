#include "jpeg.h"
#include "pgm.h"

#include <iostream>

void testJpeg(int argc, char* argv[])
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
    if ( argc < 2 )
    {
        std::cout << "No pgm file specified\n";
    }
    pgm::NetPbmImage img(argv[1]);
    std::cout << "Magic Number: " << img.headers.magic_number << std::endl;
    std::cout << "Width: " << img.headers.width << std::endl;
    std::cout << "Height: " << img.headers.height << std::endl;
    std::cout << "Max Grayscale: " << img.headers.max_grayscale << std::endl;
}

int main(int argc, char* argv[])
{
    //testEucVec();
    //testMatrix();
    //testJpeg(argc, argv);
    //testSiteswap(std::vector<unsigned int> {3, 3, 3});
    //testSiteswap(std::vector<unsigned int> {3, 2, 3}); // not valid
    //testSiteswap(std::vector<unsigned int> {4, 4, 1});
    //testSiteswap(std::vector<unsigned int> {4, 4, 2}); // not valid
    //testSiteswap(std::vector<unsigned int> {5, 5, 2});
    //testSiteswap(std::vector<unsigned int> {5, 3, 4});
    //testSiteswap(std::vector<unsigned int> {5, 0, 1});
    //testSiteswap(std::vector<unsigned int> {5, 3, 1});
    //testSiteswap(std::vector<unsigned int> {2, 3, 4, 5, 6});
    test_pgm(argc, argv);
}


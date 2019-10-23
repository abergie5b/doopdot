#include "image.h"
#include "../algorithms/resize.h"
#include "../algorithms/transform.h"
#include "../algorithms/histogram.h"
#include "../algorithms/convolution.h"
#include "../algorithms/filter.h"
#include "../formats/pgm.h"
#include "../formats/jpeg.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace image
{
    std::map<std::string, ImageType> ImageTypes = {
        {"JPG", ImageType::JPEG},
        {"JPEG", ImageType::JPEG},
        {"PGM", ImageType::PGM},
        {"PPM", ImageType::PPM},
    };

    void Image::print_headers()
    {
        std::cout << "Version: " << headers.version << std::endl;
        if (headers.comments.size() > 0)
        for (int i=0; i<headers.comments.size(); i++)
        {
            std::cout << "Comments: " << headers.comments[i] << std::endl;
        }
        std::cout << "Width/Height: " << headers.width << "/" << headers.height << std::endl;
        std::cout << "Max Grayscale: " << headers.max_grayscale << std::endl;
        std::cout << "Pixel Size: " << headers.pixel_size << " bits" << std::endl;
    }

    Image::Image(std::string _filename, std::string type)
    {
        filename = _filename;
        std::transform(type.begin(), type.end(), type.begin(), ::toupper);
        image_type = ImageTypes[type];
        if (image_type == ImageType::JPEG)
        {
            jpeg::Jpeg img(_filename);
            Headers _headers;
            _headers.version = "";
            _headers.width = img.getWidth();
            _headers.height = img.getHeight();
            _headers.max_grayscale = img.m_colourSpace;
            _headers.pixel_size = img.m_pixelSize;
            data = img.getData();
            headers = _headers;
        }
        else if (image_type == ImageType::PGM)
        {
            headers = pgm::get_headers(_filename);
            data = pgm::get_data(_filename, headers);
        }
        else if (image_type == ImageType::PPM)
        {
            headers = pgm::get_headers(_filename);
            rgb_data = pgm::get_ppm_data(_filename, headers);
        }
        else
        {
            throw std::runtime_error("i don't recognize this format");
        }
    }

    int Image::writeas(std::string path, std::string type)
    {
        std::transform(type.begin(), type.end(), type.begin(), ::toupper);
        ImageType _image_type = ImageTypes[type];
        if (_image_type == ImageType::JPEG)
        {
            return jpeg::save(headers, data, path);
        }
        else if (_image_type == ImageType::PGM) // PGM
        {
            return pgm::write(headers, data, path);
        }
        else if (_image_type == ImageType::PPM)
        {
            return pgm::write_ppm(headers, rgb_data, path);
        }
        else
        {
            throw std::runtime_error("i don't recognize this format");
        }
    }

    void Image::reset_headers()
    {
        if (image_type == ImageType::JPEG)
        {
            headers = jpeg::create_headers(filename);
        }
        else if (image_type == ImageType::PGM)
        {
            headers = pgm::create_headers(data);
        }
        else if (image_type == ImageType::PPM)
        {
            headers = pgm::create_headers(rgb_data);
        }
        else
        {
            throw std::runtime_error("i don't recognize this format");
        }
    }

    void Image::filter(std::string type)
    {
    }

    void Image::convolve(image::Kernel kernel)
    {
        if (image_type == ImageType::PPM) //grayscale
            rgb_data = algos::convolve_rgb(rgb_data, kernel);
        else
            data = algos::convolve(data, kernel);
        reset_headers();
    }

    void Image::rotate90()
    {
        data = algos::rotate90(data);
        reset_headers();
    }

    void Image::sobel()
    {
        if (image_type == ImageType::PPM)
        {
            rgb_data = algos::sobel(rgb_data);
        }
        else
        {
            data = algos::sobel(data);
        }
        reset_headers();
    }


    void Image::prewitt()
    {
        if (image_type == ImageType::PPM)
        {
            rgb_data = algos::prewitt_rgb(rgb_data);
        }
        else
        {
            data = algos::prewitt(data);
        }
        reset_headers();
    }

    void Image::negative()
    {
        data = algos::negative(data);
        reset_headers();
    }

    void Image::equalize_contrast()
    {
        data = algos::equalize_contrast(data);
        reset_headers();
    }

    std::map<image::Pixel, unsigned int> Image::get_histogram()
    {
        std::map<image::Pixel, unsigned int> hist = algos::get_histogram(data);
        return hist;
    }

    void Image::resize(size_t width, size_t height, std::string method)
    {
        if (method == "bilinear")
            data = algos::bilinear_interp(data, width, height);
        else if (method == "neighbors")
            data = algos::nearest_neighbors(data, width, height);
        else if (method == "resample")
        {
            float alpha = ((float)width * (float)height) / ((float)headers.width * (float)headers.height);
            data = algos::resize_with_resample(data, alpha);
        }
        reset_headers();
    };

    Image::~Image(){};

} // image


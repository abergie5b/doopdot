#include "include/jpeg.h"

#include <jpeglib.h>

#include <numeric>

#include <cstring>
#include <sys/stat.h>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace jpeg
{

Jpeg::Jpeg( const std::string& fileName )
{
    // Creating a custom deleter for the decompressInfo pointer
    // to ensure ::jpeg_destroy_compress() gets called even if
    // we throw out of this function.
    auto dt = []( ::jpeg_decompress_struct *ds )
            {
                ::jpeg_destroy_decompress( ds );
            };
    std::unique_ptr<::jpeg_decompress_struct, decltype(dt)> decompressInfo(
            new ::jpeg_decompress_struct,
            dt
            );

    // Note this is a shared pointer as we can share this 
    // between objects which have copy constructed from each other
    m_errorMgr = std::make_shared<::jpeg_error_mgr>();

    // Using fopen here ( and in save() ) because libjpeg expects
    // a FILE pointer.
    // We store the FILE* in a unique_ptr so we can also use the custom
    // deleter here to ensure fclose() gets called even if we throw.
    auto fdt = []( FILE* fp )
            {
                fclose( fp );
            };
    std::unique_ptr<FILE, decltype(fdt)> infile(
            fopen( fileName.c_str(), "rb" ),
            fdt
            );
    if ( infile.get() == NULL )
    {
        throw std::runtime_error( "Could not open " + fileName );
    }

    decompressInfo->err = ::jpeg_std_error( m_errorMgr.get() );
    // Note this usage of a lambda to provide our own error handler
    // to libjpeg. If we do not supply a handler, and libjpeg hits
    // a problem, it just prints the error message and calls exit().
    m_errorMgr->error_exit = [](::j_common_ptr cinfo)
        {
            char jpegLastErrorMsg[JMSG_LENGTH_MAX];
            // Call the function pointer to get the error message
            ( *( cinfo->err->format_message ) )
                ( cinfo, jpegLastErrorMsg );
            throw std::runtime_error( jpegLastErrorMsg );
        };
    ::jpeg_create_decompress( decompressInfo.get() );

    // Read the file:
    ::jpeg_stdio_src( decompressInfo.get(), infile.get() );

    int rc = ::jpeg_read_header( decompressInfo.get(), TRUE );
    if (rc != 1)
    {
        throw std::runtime_error(
            "File does not seem to be a normal JPEG"
            );
    }
    ::jpeg_start_decompress( decompressInfo.get() );

    m_width       = decompressInfo->output_width;
    m_height      = decompressInfo->output_height;
    m_pixelSize   = decompressInfo->output_components;
    m_colourSpace = decompressInfo->out_color_space;

    size_t row_stride = m_width * m_pixelSize;

    m_bitmapData.clear();
    m_bitmapData.reserve( m_height );

    while ( decompressInfo->output_scanline < m_height )
    {
        std::vector<uint8_t> vec(row_stride);
        uint8_t* p = vec.data();
        ::jpeg_read_scanlines( decompressInfo.get(), &p, 1 );
        m_bitmapData.push_back( vec );
    }
    ::jpeg_finish_decompress( decompressInfo.get() );
}

// Copy constructor
Jpeg::Jpeg( const Jpeg& rhs )
{
    m_errorMgr      = rhs.m_errorMgr;
    m_bitmapData    = rhs.m_bitmapData;
    m_width         = rhs.m_width;
    m_height        = rhs.m_height;
    m_pixelSize     = rhs.m_pixelSize;
    m_colourSpace   = rhs.m_colourSpace;
}

Jpeg::~Jpeg()
{
}

image::Headers create_headers(std::string fileName)
{
    // Creating a custom deleter for the decompressInfo pointer
    // to ensure ::jpeg_destroy_compress() gets called even if
    // we throw out of this function.
    auto dt = []( ::jpeg_decompress_struct *ds )
            {
                ::jpeg_destroy_decompress( ds );
            };
    std::unique_ptr<::jpeg_decompress_struct, decltype(dt)> decompressInfo(
            new ::jpeg_decompress_struct,
            dt
            );

    // Note this is a shared pointer as we can share this 
    // between objects which have copy constructed from each other
    std::shared_ptr<::jpeg_error_mgr> m_errorMgr;
    m_errorMgr = std::make_shared<::jpeg_error_mgr>();

    // Using fopen here ( and in save() ) because libjpeg expects
    // a FILE pointer.
    // We store the FILE* in a unique_ptr so we can also use the custom
    // deleter here to ensure fclose() gets called even if we throw.
    auto fdt = []( FILE* fp )
            {
                fclose( fp );
            };
    std::unique_ptr<FILE, decltype(fdt)> infile(
            fopen( fileName.c_str(), "rb" ),
            fdt
            );
    if ( infile.get() == NULL )
    {
        throw std::runtime_error( "Could not open " + fileName );
    }

    decompressInfo->err = ::jpeg_std_error( m_errorMgr.get() );
    // Note this usage of a lambda to provide our own error handler
    // to libjpeg. If we do not supply a handler, and libjpeg hits
    // a problem, it just prints the error message and calls exit().
    m_errorMgr->error_exit = [](::j_common_ptr cinfo)
        {
            char jpegLastErrorMsg[JMSG_LENGTH_MAX];
            // Call the function pointer to get the error message
            ( *( cinfo->err->format_message ) )
                ( cinfo, jpegLastErrorMsg );
            throw std::runtime_error( jpegLastErrorMsg );
        };
    ::jpeg_create_decompress( decompressInfo.get() );

    // Read the file:
    ::jpeg_stdio_src( decompressInfo.get(), infile.get() );

    int rc = ::jpeg_read_header( decompressInfo.get(), TRUE );
    if (rc != 1)
    {
        throw std::runtime_error(
            "File does not seem to be a normal JPEG"
            );
    }
    ::jpeg_start_decompress( decompressInfo.get() );

    image::Headers _headers;
    _headers.width = decompressInfo->output_width;
    _headers.height = decompressInfo->output_height;
    _headers.pixel_size = decompressInfo->output_components;
    _headers.max_grayscale = decompressInfo->out_color_space;
    return _headers;
}

int save(image::Headers headers, std::vector<std::vector<uint8_t>> data, const std::string& fileName)
{
    int quality = 100;
    FILE* outfile = fopen( fileName.c_str(), "wb" );
    if ( outfile == NULL )
    {
        throw std::runtime_error(
            "Could not open " + fileName + " for writing"
            );
    }
    // Creating a custom deleter for the compressInfo pointer
    // to ensure ::jpeg_destroy_compress() gets called even if
    // we throw out of this function.
    auto dt = []( ::jpeg_compress_struct *cs )
            {
                ::jpeg_destroy_compress( cs );
            };
    std::unique_ptr<::jpeg_compress_struct, decltype(dt)> compressInfo(
            new ::jpeg_compress_struct,
            dt );
    ::jpeg_create_compress( compressInfo.get() );
    ::jpeg_stdio_dest( compressInfo.get(), outfile);
    compressInfo->image_width = headers.width;
    compressInfo->image_height = headers.height;
    compressInfo->input_components = headers.pixel_size;
    compressInfo->in_color_space =
        static_cast<::J_COLOR_SPACE>( headers.max_grayscale );
    compressInfo->err = ::jpeg_std_error( NULL ); // m_errorMgr.get()
    ::jpeg_set_defaults( compressInfo.get() );
    ::jpeg_set_quality( compressInfo.get(), quality, TRUE );
    ::jpeg_start_compress( compressInfo.get(), TRUE);
    for ( auto const& vecLine : data )
    {
        ::JSAMPROW rowPtr[1];
        // Casting const-ness away here because the jpeglib
        // call expects a non-const pointer. It presumably
        // doesn't modify our data.
        rowPtr[0] = const_cast<::JSAMPROW>( vecLine.data() );
        ::jpeg_write_scanlines(
            compressInfo.get(),
            rowPtr,
            1
            );
    }
    ::jpeg_finish_compress( compressInfo.get() );
    fclose( outfile );
    struct stat s;
    if (stat(fileName.c_str(), &s) == -1)
        throw std::runtime_error(std::strerror(errno));
    return s.st_size;
}

void Jpeg::savePpm( const std::string& fileName ) const
{
    std::ofstream ofs( fileName, std::ios::out | std::ios::binary );
    if ( ! ofs )
    {
        throw std::runtime_error(
            "Could not open " + fileName + " for saving"
            );
    }
    // Write the header
    ofs << "P6 " << m_width << " " << m_height << " 255\n";
    for ( auto& v : m_bitmapData )
    {
        ofs.write( reinterpret_cast<const char *>(v.data()), v.size() );
    }
    ofs.close();
}

std::vector<std::vector<uint8_t>> Jpeg::getData()
{
    return m_bitmapData;
}

} // namespace jpeg



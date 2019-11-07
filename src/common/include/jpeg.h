#pragma once

#include "headers.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

// forward declarations of jpeglib struct
struct jpeg_error_mgr;

namespace jpeg
{
int save(image::Headers headers, std::vector<std::vector<uint8_t>> data, const std::string& fileName);
image::Headers create_headers(std::string fileName);

class Jpeg
{
public:
    // Currently can only construct with an existing file.
    // Will throw if file cannot be loaded, or is in the wrong format,
    // or some other error is encountered.
    explicit Jpeg( const std::string& fileName );

    // We can construct from an existing image object. This allows us
    // to work on a copy (e.g. shrink then save) without affecting the
    // original we have in memory.
    Jpeg( const Jpeg& rhs );

    // But assigment and move operations are currently disallowed
    Jpeg& operator=( const Jpeg& ) = delete;
    Jpeg( Jpeg&& )                 = delete;
    Jpeg& operator=( Jpeg&& )      = delete;

    ~Jpeg();

    // Mainly for testing, writes an uncompressed PPM file
    void savePpm( const std::string& fileName ) const;

    size_t getHeight()    const { return m_height; }
    size_t getWidth()     const { return m_width;  }
    size_t getPixelSize() const { return m_pixelSize; }
    std::vector<std::vector<uint8_t>> getData();

    size_t                            m_pixelSize;
    int                               m_colourSpace;
private:
    // Note that m_errorMgr is a shared ptr and will be shared
    // between objects if one copy constructs from another
    std::shared_ptr<::jpeg_error_mgr> m_errorMgr;
    std::vector<std::vector<uint8_t>> m_bitmapData;
    size_t                            m_width;
    size_t                            m_height;
};

} // namespace jpeg



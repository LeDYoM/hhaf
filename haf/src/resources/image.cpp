#include <haf/include/resources/image.hpp>
#include <hogl/include/types.hpp>
#include "stb_image/stb_image.h"

using namespace haf::core;
using namespace haf::math;

namespace
{
/*
void generate_texture(float* data, int width, int height)
{
    int x, y;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            data[(y * width + x) * 4 + 0] = (float)((x & y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 1] = (float)((x | y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 2] = (float)((x ^ y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 3] = 1.0f;
        }
    }
}
*/
}  // namespace

namespace haf::res
{
struct Image::ImagePrivate
{
    u8* m_data{nullptr};
    ImageSize m_size{0U, 0U};
    fast_u8 m_chanels{0U};

    bool setPixel(Coordinate const& where, RGBAPixel const& pixel) noexcept
    {
        if (m_data != nullptr && where.x < m_size.x && where.y < m_size.y)
        {
            auto* pixelOffset{m_data +
                              (where.x + (m_size.y * where.y)) * m_chanels};
            pixelOffset[0U] = pixel.x;

            if (m_chanels > 1U)
            {
                pixelOffset[1U] = pixel.y;
            }

            if (m_chanels > 2U)
            {
                pixelOffset[2U] = pixel.z;
            }

            if (m_chanels > 3U)
            {
                pixelOffset[3U] = pixel.w;
            }
            return true;
        }
        return false;
    }

    RGBAPixel getPixel(Coordinate const& where) const noexcept
    {
        RGBAPixel result{PixelChannel{}, PixelChannel{}, PixelChannel{},
                         PixelChannel{}};

        if (m_data != nullptr && where.x < m_size.x && where.y < m_size.y)
        {
            auto* pixelOffset{m_data +
                              (where.x + (m_size.y * where.y)) * m_chanels};
            result =
                RGBAPixel{pixelOffset[0], pixelOffset[1], pixelOffset[2],
                          (m_chanels > 3U ? pixelOffset[3]
                                          : static_cast<PixelChannel>(0xFF))};
        }
        return result;
    }

    constexpr bool validCoordinates(Coordinate const& coordinate) const noexcept
    {
        return coordinate.x < m_size.x && coordinate.y < m_size.y;
    }

    ~ImagePrivate() noexcept
    {
        if (m_data != nullptr)
        {
            //            stbi_image_free(m_data);
            std::free(m_data);
        }
    }
};

Image::Image() noexcept : m_p{make_pimplp<ImagePrivate>()}
{}

Image::Image(str_view fileName) noexcept : Image{}
{
    (void)(fileName);
    int width, height, nrChannels;
    m_p->m_data = stbi_load("zoperbl.png", &width, &height, &nrChannels, 0);
    if (m_p->m_data)
    {
        m_p->m_size =
            vector2du32{static_cast<u32>(width), static_cast<u32>(height)};
        m_p->m_chanels = static_cast<fast_u8>(nrChannels);
    }

    //   generate_texture(m_p->data, 256, 256);
}

Image::Image(Coordinate const& image_size, const u8 bpp) noexcept : Image{}
{
    m_p->m_data    = new PixelChannel[image_size.x * image_size.y * bpp];
    m_p->m_size    = image_size;
    m_p->m_chanels = bpp;
}

Image::~Image()
{}

Image::PixelChannel const* Image::data() const noexcept
{
    return m_p->m_data;
}

vector2du32 Image::size() const noexcept
{
    return m_p->m_size;
}

u32 Image::channels() const noexcept
{
    return static_cast<u32>(m_p->m_chanels);
}

bool Image::containsImage() const noexcept
{
    return m_p->m_data != nullptr;
}

bool Image::isValid() const noexcept
{
    return containsImage();
}

bool Image::setPixel(vector2du32 const& where, RGBAPixel const& pixel) noexcept
{
    return m_p != nullptr ? m_p->setPixel(where, pixel) : false;
}

Image::RGBAPixel Image::getPixel(vector2du32 const& where) const noexcept
{
    return m_p != nullptr ? m_p->getPixel(where) : Image::RGBAPixel{};
}

bool Image::validCoordinates(Coordinate const& coordinate) const noexcept
{
    return m_p->validCoordinates(coordinate);
}

bool Image::fill(Coordinate const& start,
                 Coordinate const& end,
                 RGBAPixel const& pixel) noexcept
{
    if (isValid() && validCoordinates(start) && validCoordinates(end) &&
        start.x <= end.x && start.y <= end.y)
    {
        for (auto y{start.y}; y <= end.y; ++y)
        {
            for (auto x{start.x}; x <= end.x; ++x)
            {
                setPixel({x, y}, pixel);
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

void Image::fill(RGBAPixel const& pixel) noexcept
{
    (void)(fill({0U, 0U}, {m_p->m_size.x - 1U, m_p->m_size.y - 1U}, pixel));
}

}  // namespace haf::res

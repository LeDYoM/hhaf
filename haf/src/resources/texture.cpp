#include <haf/include/resources/texture.hpp>
#include <hogl/include/types.hpp>
#include <hogl/include/texture_functions.hpp>

#include <hlog/include/hlog.hpp>

#include "glad/glad.h"

using namespace haf::core;

namespace
{
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
}  // namespace

namespace haf::res
{
struct Texture::TexturePrivate
{
    ogl::Handle m_texture{ogl::invalidHandle()};
};

Texture::Texture() : m_p{make_pimplp<TexturePrivate>()}
{
    m_p->m_texture = ogl::createTexture();

    // Specify the amount of storage we want to use for the texture
    glTextureStorage2D(m_p->m_texture,
                       1,           // 8 mipmap levels
                       GL_RGBA32F,  // 32-bit floating-point RGBA data
                       256, 256);   // 256 x 256 texels

    // Define some data to upload into the texture
    float* data = new float[256 * 256 * 4];

    // generate_texture() is a function that fills memory with image data
    generate_texture(data, 256, 256);

    // Assume the texture is already bound to the GL_TEXTURE_2D target
    glTextureSubImage2D(m_p->m_texture,  // 2D texture
                        0,               // Level 0
                        0, 0,            // Offset 0, 0
                        256, 256,  // 256 x 256 texels, replace entire image
                        GL_RGBA,   // Four channel data
                        GL_FLOAT,  // Floating point data
                        data);     // Pointer to data

    // Free the memory we allocated before - \GL now has our data
    delete[] data;
}

Texture::Texture(Image const& image) : m_p{make_pimplp<TexturePrivate>()}
{
    m_p->m_texture = ogl::createTexture();

    ogl::TextureCreationParameters texture_cp;
    texture_cp.imageFormat =
        image.channels() == 4U ? ogl::ImageFormat::Rgba : ogl::ImageFormat::Rgb;
    texture_cp.mipmaps = 1U;
    texture_cp.size    = image.size();

    ogl::textureStorage(m_p->m_texture, texture_cp);

    ogl::SubImageCreationParameters sub_image_cp;
    sub_image_cp.imageFormat =
        image.channels() == 4U ? ogl::ImageFormat::Rgba : ogl::ImageFormat::Rgb;
    sub_image_cp.mipmap = 0;
    sub_image_cp.data = image.data();
    sub_image_cp.rect = Rectu32{0,0,image.size()};
    ogl::updateTexture(m_p->m_texture, sub_image_cp);
}

Texture::~Texture()
{
    ogl::destroyTexture(m_p->m_texture);
    m_p->m_texture = ogl::invalidHandle();
}

bool Texture::isValid() const
{
    return m_p != nullptr && ogl::isValid(m_p->m_texture);
}

}  // namespace haf::res

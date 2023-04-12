#include <haf/include/resources/texture.hpp>
#include <hogl/include/types.hpp>
#include <hogl/include/texture_functions.hpp>
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
                   1,              // 8 mipmap levels
                   GL_RGBA32F,     // 32-bit floating-point RGBA data
                   256, 256);      // 256 x 256 texels

    // Define some data to upload into the texture
    float* data = new float[256 * 256 * 4];

    // generate_texture() is a function that fills memory with image data
        generate_texture(data, 256, 256);

    // Assume the texture is already bound to the GL_TEXTURE_2D target
    glTextureSubImage2D(m_p->m_texture,  // 2D texture
                    0,              // Level 0
                    0, 0,           // Offset 0, 0
                    256, 256,       // 256 x 256 texels, replace entire image
                    GL_RGBA,        // Four channel data
                    GL_FLOAT,       // Floating point data
                    data);          // Pointer to data

    // Free the memory we allocated before - \GL now has our data
    delete[] data;
}

Texture::Texture(Image const& image) : m_p{make_pimplp<TexturePrivate>()}
{
    m_p->m_texture = ogl::createTexture();
/*
    // Specify the amount of storage we want to use for the texture
    glTextureStorage2D(m_p->m_texture,
                   1,              // 8 mipmap levels
                   GL_RGBA32F,     // 32-bit floating-point RGBA data
                   256, 256);      // 256 x 256 texels
*/

    GLenum internal_format{GL_RGBA8};
    GLenum format{GL_RGBA};
    GLenum type{GL_UNSIGNED_BYTE};
    if (image.channels() == 4)
    {
        internal_format = GL_RGBA8;
        format = GL_RGBA;
        type = GL_UNSIGNED_BYTE;
    }
    else if (image.channels() == 3)
    {
        internal_format = GL_RGB8;
        format = GL_RGB;
        type = GL_UNSIGNED_BYTE;
    }

    glTextureStorage2D(m_p->m_texture,
                   1,              // 8 mipmap levels
                   internal_format,     // 32-bit floating-point RGBA data
                   image.size().x, image.size().y);      // 256 x 256 texels

    // Assume the texture is already bound to the GL_TEXTURE_2D target
    glTextureSubImage2D(m_p->m_texture,  // 2D texture
                    0,              // Level 0
                    0, 0,           // Offset 0, 0
                    image.size().x, image.size().y,       // 256 x 256 texels, replace entire image
                    format,        // Four channel data
                    type,       // Floating point data
                    image.data());          // Pointer to data
}

Texture::~Texture()
{
    ogl::destroyTexture(m_p->m_texture);
    m_p->m_texture = ogl::invalidHandle();
}

}  // namespace haf::res

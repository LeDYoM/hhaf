#include <hogl/include/texture_functions.hpp>
#include <glad/glad.h>

using namespace htps;

namespace haf::ogl
{
Handle createTexture() noexcept
{
    Handle result{ogl::invalidHandle()};
    glCreateTextures(GL_TEXTURE_2D, 1, &result);
    return result;
}

void destroyTexture(Handle const handle) noexcept
{
    glDeleteTextures(1, &handle);
}

void textureStorage(Handle const handle,
                    TextureCreationParameters const& params) noexcept
{
    // Select OpenGL format according to image format
    GLenum internal_format{GL_RGBA8};

    if (params.imageFormat == ImageFormat::Rgba)
    {
        internal_format = GL_RGBA8;
    }
    else if (params.imageFormat == ImageFormat::Rgb)
    {
        internal_format = GL_RGB8;
    }

    glTextureStorage2D(handle, params.mipmaps, internal_format, params.size.x,
                       params.size.y);
}

void updateTexture(Handle const handle,
                   SubImageCreationParameters const& params) noexcept
{
    GLenum format{GL_RGBA};
    if (params.imageFormat == ImageFormat::Rgba)
    {
        format = GL_RGBA;
    }
    else if (params.imageFormat == ImageFormat::Rgb)
    {
        format = GL_RGB;
    }

    // Assume the texture is already bound to the GL_TEXTURE_2D target
    glTextureSubImage2D(
        handle,                             // 2D texture
        params.mipmap,                      // Level 0
        params.rect.left, params.rect.top,  // Offset 0, 0
        params.rect.width,
        params.rect.height,  // 256 x 256 texels, replace entire image
        format,              // Four channel data
        GL_UNSIGNED_BYTE,    // Floating point data
        params.data);        // Pointer to data
}

}  // namespace haf::ogl
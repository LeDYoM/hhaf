#ifndef HAF_OGL_SHADER_INCLUDE_HPP
#define HAF_OGL_SHADER_INCLUDE_HPP

#include <hogl/include/ogl_export.hpp>
#include <hogl/include/types.hpp>
#include <htypes/include/str.hpp>

namespace haf::ogl
{
enum ImageFormat : htps::u32
{
    Rgb  = 0U,
    Rgba = 1,
};

struct TextureCreationParameters
{
    htps::u32 mipmaps;
    fmath::vector2du32 size;
    ImageFormat imageFormat;
};

struct SubImageCreationParameters
{
    htps::u32 mipmap;
    fmath::Rectu32 rect;
    ImageFormat imageFormat;
    const htps::u8* data;
};

[[nodiscard]] HOGL_API Handle createTexture() noexcept;
HOGL_API void destroyTexture(Handle const handle) noexcept;
HOGL_API void textureStorage(Handle const handle,
                             TextureCreationParameters const& params) noexcept;
HOGL_API void updateTexture(Handle const handle,
                             SubImageCreationParameters const& params) noexcept;

}  // namespace haf::ogl

#endif

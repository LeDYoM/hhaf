#ifndef HAF_BACKEND_IRESOURCE_DESCRIPTOR_INCLUDE_HPP
#define HAF_BACKEND_IRESOURCE_DESCRIPTOR_INCLUDE_HPP

#include <htypes/include/str.hpp>

namespace haf::backend
{
static constexpr char const kResourceTexture[] = "texture";
static constexpr char const kResourceTTFont[] = "ttf";
static constexpr char const kResourceBMPFont[] = "bmp_font_fnt";
static constexpr char const kResourceShader[] = "shader";

struct IResourceDescriptor
{
    htps::str name;
    htps::str type;
    htps::str fileName;
};
}  // namespace haf::res

#endif
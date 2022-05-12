HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_RESOURCE_DESCRIPTOR_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCE_DESCRIPTOR_INCLUDE_HPP

#include <htypes/include/str.hpp>

namespace haf::res
{
static constexpr char const kResourceTexture[] = "texture";
static constexpr char const kResourceTTFont[] = "ttf";
static constexpr char const kResourceBMPFont[] = "bmp_font_fnt";
static constexpr char const kResourceShader[] = "shader";

struct ResourceDescriptor
{
    htps::str name;
    htps::str type;
    htps::str fileName;
};
}  // namespace haf::res

#endif
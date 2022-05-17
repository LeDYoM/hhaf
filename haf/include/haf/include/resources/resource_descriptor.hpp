HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_RESOURCE_DESCRIPTOR_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCE_DESCRIPTOR_INCLUDE_HPP

#include <backend_dev/include/iresource_descriptor.hpp>

namespace haf::res
{
static constexpr char const kResourceTexture[] = "texture";
static constexpr char const kResourceTTFont[]  = "ttf";
static constexpr char const kResourceBMPFont[] = "bmp_font_fnt";
static constexpr char const kResourceShader[]  = "shader";

using ResourceDescriptor = backend::IResourceDescriptor;

inline backend::IResourceDescriptor to_backend(ResourceDescriptor const& rd)
{
    return static_cast<backend::IResourceDescriptor>(rd);
}
}  // namespace haf::res

#endif
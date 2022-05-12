HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLE_OBJECT_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_OBJECT_DATA_INCLUDE_HPP

#include <haf/include/render/renderizable_data.hpp>
#include <htypes/include/property_group.hpp>

namespace haf::res
{
class IShader;
class ITexture;
}  // namespace haf::res

namespace haf::render
{
using RenderizableObjectData = htps::PropertyGroup<ColorProperty,
                                                   ShaderProperty,
                                                   TextureProperty,
                                                   TextureRectProperty>;
}  // namespace haf::render

#endif

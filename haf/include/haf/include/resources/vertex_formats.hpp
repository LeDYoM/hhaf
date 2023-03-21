HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RESOURCE_VERTEX_FORMATS_INCLUDE_HPP
#define HAF_RENDER_RESOURCE_VERTEX_FORMATS_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>

namespace haf::res
{
struct Position3fNormal3fTextureCoordinates2f
{
    core::vector3df position;
    core::vector3df normal;
    core::vector2df textureuv;
};
}  // namespace haf::res

#endif

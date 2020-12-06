#ifndef HAF_SCENE_PRIMITIVE_TYPE_INCLUDE_HPP
#define HAF_SCENE_PRIMITIVE_TYPE_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace haf::scene
{
enum class PrimitiveType : mtps::u8
{
    Points = 0U,
    Lines,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan
};

}  // namespace haf::scene

#endif

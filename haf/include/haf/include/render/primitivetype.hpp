#ifndef HAF_SCENE_PRIMITIVE_TYPE_INCLUDE_HPP
#define HAF_SCENE_PRIMITIVE_TYPE_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::render
{
enum class PrimitiveType : htps::u8
{
    Points = 0U,
    Lines,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan
};

}  // namespace haf::render

#endif

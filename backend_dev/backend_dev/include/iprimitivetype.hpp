#ifndef HAF_BACKEND_DEV_IPRIMITIVE_TYPE_INCLUDE_HPP
#define HAF_BACKEND_DEV_IPRIMITIVE_TYPE_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace haf::backend
{
enum class iPrimitiveType : mtps::u8
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

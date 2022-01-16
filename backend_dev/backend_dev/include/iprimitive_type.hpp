#ifndef HAF_BACKEND_DEV_IPRIMITIVE_TYPE_INCLUDE_HPP
#define HAF_BACKEND_DEV_IPRIMITIVE_TYPE_INCLUDE_HPP

#include <htypes/include/types.hpp>

namespace haf::backend
{
enum class iPrimitiveType : htps::u8
{
    Points = 0U,
    Lines,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan
};

}  // namespace haf::backend

#endif

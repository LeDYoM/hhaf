#ifndef HAF_BACKEND_RENDER_DATA_INCLUDE_HPP
#define HAF_BACKEND_RENDER_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include "ivertex.hpp"
#include "iprimitive_type.hpp"

namespace haf::backend
{
class ITexture;
class IShader;

struct IRenderData
{
    iVertex const* vertices;
    htps::size_type const nVertex;
    iPrimitiveType const pType;
    htps::f32 const* transform;
    ITexture const* texture;
    IShader const* shader;
};
}  // namespace haf::backend

#endif

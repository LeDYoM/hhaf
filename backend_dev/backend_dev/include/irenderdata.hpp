#ifndef HAF_BACKEND_RENDER_DATA_INCLUDE_HPP
#define HAF_BACKEND_RENDER_DATA_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "ivertex.hpp"
#include "iprimitivetype.hpp"

namespace haf::backend
{
class ITexture;
class IShader;

struct IRenderData
{
    const iVertex* vertices;
    const mtps::size_type nVertex;
    const iPrimitiveType pType;
    const mtps::f32* transform;
    const ITexture* texture;
    const IShader* shader;
};
}  // namespace haf::backend

#endif

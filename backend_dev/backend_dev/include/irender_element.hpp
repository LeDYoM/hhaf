#ifndef HAF_BACKEND_DEV_IRENDER_ELEMENT_TYPE_INCLUDE_HPP
#define HAF_BACKEND_DEV_IRENDER_ELEMENT_TYPE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include "ivertex.hpp"
#include "iprimitive_type.hpp"

namespace haf::backend
{
class ITexture;
class IShader;

class IRenderElement
{
public:
    virtual void setSize(htps::size_type const size)             = 0;
    virtual void setVertexData(iVertex const* const vertex_data) = 0;
    virtual void setTexture(ITexture const* const texture)       = 0;
    virtual void setModelViewMatrix(
        htps::f32 const* const model_view_matrix) = 0;
    virtual void setProjectionMatrix(
        htps::f32 const* const projection_matrix)        = 0;
    virtual void setShader(IShader const* const texture) = 0;
};
}  // namespace haf::backend

#endif

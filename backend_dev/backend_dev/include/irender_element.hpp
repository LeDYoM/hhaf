#ifndef HAF_BACKEND_DEV_IRENDER_ELEMENT_TYPE_INCLUDE_HPP
#define HAF_BACKEND_DEV_IRENDER_ELEMENT_TYPE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include "ivertex.hpp"

namespace haf::backend
{
class ITexture;
class IShader;

class IRenderElement
{
public:
    virtual ~IRenderElement() = default;
    virtual void setSize(htps::size_type const size)            = 0;
    virtual void setPositions(iPosition const* const positions) = 0;
    virtual void setColors(iColor const* const colors)          = 0;
    virtual void setTexturecoordinates(
        iTextureCoordinates const* const texture_coordinates) = 0;
    virtual void setTexture(ITexture const* const texture)    = 0;
    virtual void setModelViewMatrix(
        htps::f32 const* const model_view_matrix) = 0;
    virtual void setProjectionMatrix(
        htps::f32 const* const projection_matrix)        = 0;
    virtual void setShader(IShader const* const texture) = 0;
};
}  // namespace haf::backend

#endif

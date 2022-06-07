HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDER_ELEMENT_INCLUDE_HPP
#define HAF_RENDER_RENDER_ELEMENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <backend_dev/include/ivertex.hpp>

namespace haf::backend
{
class IRenderElement;
class ITexture;
class IShader;
}  // namespace haf::backend

namespace haf::render
{
class RenderElement
{
public:
    explicit RenderElement(
        htps::uptr<backend::IRenderElement> irender_element) noexcept;
    void setSize(htps::size_type const size);
    void setPositions(backend::iPosition const* const positions);
    void setColors(backend::iColor const* const colors);
    void setTexturecoordinates(
        backend::iTextureCoordinates const* const texture_coordinates);
    void setTexture(backend::ITexture const* const texture);
    void setModelViewMatrix(htps::f32 const* const model_view_matrix);
    void setProjectionMatrix(htps::f32 const* const projection_matrix);
    void setShader(backend::IShader const* const shader);

    htps::rptr<backend::IRenderElement const> irenderElement() const;
private:
    htps::uptr<backend::IRenderElement> m_irender_element;
};
}  // namespace haf::render

#endif

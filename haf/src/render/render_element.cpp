#include "render_element.hpp"
#include <backend_dev/include/irender_element.hpp>

using namespace htps;

namespace haf::render
{
RenderElement::RenderElement(
    uptr<backend::IRenderElement> irender_element) noexcept :
    m_irender_element{htps::move(irender_element)}
{}

void RenderElement::setSize(htps::size_type const size)
{
    m_irender_element->setSize(size);
}

void RenderElement::setPositions(backend::iPosition const* const positions)
{
    m_irender_element->setPositions(positions);
}

void RenderElement::setColors(backend::iColor const* const colors)
{
    m_irender_element->setColors(colors);
}

void RenderElement::setTexturecoordinates(
    backend::iTextureCoordinates const* const texture_coordinates)
{
    m_irender_element->setTexturecoordinates(texture_coordinates);
}
void RenderElement::setTexture(backend::ITexture const* const texture)
{
    m_irender_element->setTexture(texture);
}
void RenderElement::setModelViewMatrix(htps::f32 const* const model_view_matrix)
{
    m_irender_element->setModelViewMatrix(model_view_matrix);
}
void RenderElement::setProjectionMatrix(
    htps::f32 const* const projection_matrix)
{
    m_irender_element->setProjectionMatrix(projection_matrix);
}
void RenderElement::setShader(backend::IShader const* const shader)
{
    m_irender_element->setShader(shader);
}

rptr<backend::IRenderElement const> RenderElement::irenderElement() const
{
    return m_irender_element.get();
}

}  // namespace haf::render

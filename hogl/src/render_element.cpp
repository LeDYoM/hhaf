#include <hogl/include/render_element.hpp>
#include <backend_dev/include/ishader.hpp>

using namespace haf::backend;

namespace haf::ogl
{
RenderElement::RenderElement() :
    vertex_buffer_{VertexBuffer::Usage::Dynamic},
    vertex_buffer_origin_{},
    needs_update_{true}
{}

void RenderElement::setTexture(ITexture const* const p_texture)
{
    texture = p_texture;
}

void RenderElement::setModelViewMatrix(htps::f32 const* const model_view_matrix)
{
    transformation = htps::span(model_view_matrix, model_view_matrix + 16U);
}

void RenderElement::setProjectionMatrix(
    htps::f32 const* const /*projection_matrix*/)
{}

void RenderElement::setShader(IShader const* const p_shader)
{
    shader = const_cast<IShader*>(p_shader);
}

void RenderElement::setSize(htps::size_type const size)
{
    vertex_buffer_.create(static_cast<std::size_t>(size));
    vertex_buffer_origin_.resize(size);
    needs_update_ = true;
}

void RenderElement::setPositions(iPosition const* const positions)
{
    iPosition const* vtemp{positions};
    for (auto&& vertex_buffer_origin_element : vertex_buffer_origin_)
    {
        vertex_buffer_origin_element.position = *vtemp;
        ++vtemp;
    }
    needs_update_ = true;
}

void RenderElement::setColors(iColor const* const colors)
{
    iColor const* vtemp{colors};
    for (auto&& vertex_buffer_origin_element : vertex_buffer_origin_)
    {
        vertex_buffer_origin_element.color = *vtemp;
        ++vtemp;
    }
    needs_update_ = true;
}

void RenderElement::setTexturecoordinates(
    iTextureCoordinates const* const texture_coordinates)
{
    iTextureCoordinates const* vtemp{texture_coordinates};
    for (auto&& vertex_buffer_origin_element : vertex_buffer_origin_)
    {
        vertex_buffer_origin_element.texture_coordinates = *vtemp;
        ++vtemp;
    }
    needs_update_ = true;
}

void RenderElement::updateInternalData() const
{
    if (needs_update_)
    {
        vertex_buffer_.update(vertex_buffer_origin_.cbegin());
        needs_update_ = false;
    }
}

VertexBuffer const& RenderElement::vertexBuffer() const noexcept
{
    return vertex_buffer_;
}

}  // namespace haf::ogl

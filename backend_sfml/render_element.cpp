#include "render_element.hpp"
#include "conversions.hpp"

namespace haf::backend::sfmlb
{
RenderElement::~RenderElement() = default;

void RenderElement::setPrimitiveType(iPrimitiveType const primitive_type)
{
    vertex_array_.setPrimitiveType(to_sf_type(primitive_type));
}

void RenderElement::setSize(htps::size_type const size)
{
    vertex_array_.resize(static_cast<std::size_t>(size));
}

void RenderElement::setVertexData(iVertex const* const vertex_data)
{
    for (auto i{0U}; i < vertex_array_.getVertexCount(); ++i)
    {
        vertex_array_[i] = to_sf_type(*vertex_data);
    }
}

void RenderElement::setTexture(ITexture const* const texture)
{
    render_states_.texture = to_sf_type(texture);
}

void RenderElement::setModelViewMatrix(htps::f32 const* const model_view_matrix)
{
    render_states_.transform = to_sf_type(model_view_matrix);
}

void RenderElement::setProjectionMatrix(
    htps::f32 const* const /*projection_matrix*/)
{}

void RenderElement::setShader(IShader const* const shader)
{
    render_states_.shader = to_sf_type(shader);
}
}  // namespace haf::backend::sfmlb

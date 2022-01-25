#include "render_element.hpp"

namespace haf::backend::sfmlb
{
void RenderElement::setSize(htps::size_type const size)
{
    vertex_array_.resize(static_cast<std::size_t>(size));
}

void RenderElement::setVertexData(iVertex const* const vertex_data)
{
    for (auto i{0U}; i < vertex_array_.getVertexCount(); ++i)
    {
        vertex_array_[i] = sf::Vertex{};
    }
}

void RenderElement::setTexture(ITexture const* const texture)
{}

void RenderElement::setModelViewMatrix(htps::f32 const* const model_view_matrix)
{}

void RenderElement::setProjectionMatrix(
    htps::f32 const* const projection_matrix)
{}

void RenderElement::setTexture(ITexture const* const texture)
{}
}  // namespace haf::backend::sfmlb

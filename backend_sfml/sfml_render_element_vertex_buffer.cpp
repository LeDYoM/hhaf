#include "sfml_render_element_vertex_buffer.hpp"
#include "conversions.hpp"

namespace haf::backend::sfmlb
{
SFMLRenderElementVertexBuffer::~SFMLRenderElementVertexBuffer() = default;
#ifdef USE_VERTEX_ARRAY
void SFMLRenderElementVertexBuffer::setPositions(
    iPosition const* const positions)
{
    iPosition const* vtemp{positions};
    for (auto i{0U}; i < vertex_array_.getVertexCount(); ++i)
    {
        vertex_array_[i].position = to_sf_type(*vtemp);
        ++vtemp;
    }
}

void SFMLRenderElementVertexBuffer::setColors(iColor const* const colors)
{
    iColor const* vtemp{colors};
    for (auto i{0U}; i < vertex_array_.getVertexCount(); ++i)
    {
        vertex_array_[i].color = to_sf_type(*vtemp);
        ++vtemp;
    }
}

void SFMLRenderElementVertexBuffer::setTexturecoordinates(
    iTextureCoordinates const* const texture_coordinates)
{
    iTextureCoordinates const* vtemp{texture_coordinates};
    for (auto i{0U}; i < vertex_array_.getVertexCount(); ++i)
    {
        vertex_array_[i].texCoords = to_sf_type(*vtemp);
        ++vtemp;
    }
}

void SFMLRenderElementVertexBuffer::setSize(htps::size_type const size)
{
    vertex_array_.resize(static_cast<std::size_t>(size));
}

void SFMLRenderElementVertexBuffer::setTexture(ITexture const* const texture)
{
    render_states_.texture = to_sf_type(texture);
}

void SFMLRenderElementVertexBuffer::setModelViewMatrix(
    htps::f32 const* const model_view_matrix)
{
    render_states_.transform = to_sf_type(model_view_matrix);
}

void SFMLRenderElementVertexBuffer::setProjectionMatrix(
    htps::f32 const* const /*projection_matrix*/)
{}

void SFMLRenderElementVertexBuffer::setShader(IShader const* const shader)
{
    render_states_.shader = to_sf_type(shader);
}

void SFMLRenderElementVertexBuffer::render(sf::RenderTarget& target) const
{
    if (render_states_.shader != nullptr)
    {
        sf::Shader* shader{const_cast<sf::Shader*>(render_states_.shader)};
        if (render_states_.texture != nullptr)
        {
            shader->setUniform("has_texture", true);
            shader->setUniform("texture", sf::Shader::CurrentTexture);
        }
        else
        {
            shader->setUniform("has_texture", false);
            //                shader->setUniform("texture", nullptr);
        }
    }

    target.draw(vertex_array_, render_states_);
}
#else
void SFMLRenderElementVertexBuffer::setPositions(
    iPosition const* const positions)
{
    iPosition const* vtemp{positions};
    for (auto i{0U}; i < vertex_buffer_origin_.size(); ++i)
    {
        vertex_buffer_origin_[i].position = to_sf_type(*vtemp);
        ++vtemp;
    }
    needs_update_ = true;
}

void SFMLRenderElementVertexBuffer::setSize(htps::size_type const size)
{
    vertex_buffer_.create(static_cast<std::size_t>(size));
    vertex_buffer_origin_.resize(size);
    needs_update_ = true;
}

void SFMLRenderElementVertexBuffer::setColors(iColor const* const colors)
{
    iColor const* vtemp{colors};
    for (auto i{0U}; i < vertex_buffer_origin_.size(); ++i)
    {
        vertex_buffer_origin_[i].color = to_sf_type(*vtemp);
        ++vtemp;
    }
    needs_update_ = true;
}

void SFMLRenderElementVertexBuffer::setTexturecoordinates(
    iTextureCoordinates const* const texture_coordinates)
{
    iTextureCoordinates const* vtemp{texture_coordinates};
    for (auto i{0U}; i < vertex_buffer_origin_.size(); ++i)
    {
        vertex_buffer_origin_[i].texCoords = to_sf_type(*vtemp);
        ++vtemp;
    }
    needs_update_ = true;
}

void SFMLRenderElementVertexBuffer::setTexture(ITexture const* const texture)
{
    render_states_.texture = to_sf_type(texture);
}

void SFMLRenderElementVertexBuffer::setModelViewMatrix(
    htps::f32 const* const model_view_matrix)
{
    render_states_.transform = to_sf_type(model_view_matrix);
}

void SFMLRenderElementVertexBuffer::setProjectionMatrix(
    htps::f32 const* const /*projection_matrix*/)
{}

void SFMLRenderElementVertexBuffer::setShader(IShader const* const shader)
{
    render_states_.shader = to_sf_type(shader);
}

void SFMLRenderElementVertexBuffer::render(sf::RenderTarget& target) const
{
    if (needs_update_)
    {
        vertex_buffer_.update(vertex_buffer_origin_.cbegin());
        needs_update_ = false;
    }
    target.draw(vertex_buffer_, render_states_);
}

#endif
}  // namespace haf::backend::sfmlb

#include "sfml_render_element.hpp"
#include "conversions.hpp"

namespace haf::backend::sfmlb
{
SFMLRenderElement::~SFMLRenderElement() = default;
#ifdef USE_VERTEX_ARRAY
void SFMLRenderElement::setPositions(
    iPosition const* const positions)
{
    iPosition const* vtemp{positions};
    for (auto i{0U}; i < vertex_array_.getVertexCount(); ++i)
    {
        vertex_array_[i].position = to_sf_type(*vtemp);
        ++vtemp;
    }
}

void SFMLRenderElement::setColors(iColor const* const colors)
{
    iColor const* vtemp{colors};
    for (auto i{0U}; i < vertex_array_.getVertexCount(); ++i)
    {
        vertex_array_[i].color = to_sf_type(*vtemp);
        ++vtemp;
    }
}

void SFMLRenderElement::setTexturecoordinates(
    iTextureCoordinates const* const texture_coordinates)
{
    iTextureCoordinates const* vtemp{texture_coordinates};
    for (auto i{0U}; i < vertex_array_.getVertexCount(); ++i)
    {
        vertex_array_[i].texCoords = to_sf_type(*vtemp);
        ++vtemp;
    }
}

void SFMLRenderElement::setSize(htps::size_type const size)
{
    vertex_array_.resize(static_cast<std::size_t>(size));
}

void SFMLRenderElement::setTexture(ITexture const* const texture)
{
    render_states_.texture = to_sf_type(texture);
}

void SFMLRenderElement::setModelViewMatrix(
    htps::f32 const* const model_view_matrix)
{
    render_states_.transform = to_sf_type(model_view_matrix);
}

void SFMLRenderElement::setProjectionMatrix(
    htps::f32 const* const /*projection_matrix*/)
{}

void SFMLRenderElement::setShader(IShader const* const shader)
{
    render_states_.shader = to_sf_type(shader);
}

void SFMLRenderElement::render(sf::RenderTarget& target) const
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
void SFMLRenderElement::setPositions(
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

void SFMLRenderElement::setSize(htps::size_type const size)
{
    vertex_buffer_.create(static_cast<std::size_t>(size));
    vertex_buffer_origin_.resize(size);
    needs_update_ = true;
}

void SFMLRenderElement::setColors(iColor const* const colors)
{
    iColor const* vtemp{colors};
    for (auto i{0U}; i < vertex_buffer_origin_.size(); ++i)
    {
        vertex_buffer_origin_[i].color = to_sf_type(*vtemp);
        ++vtemp;
    }
    needs_update_ = true;
}

void SFMLRenderElement::setTexturecoordinates(
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

void SFMLRenderElement::setTexture(ITexture const* const texture)
{
    render_states_.texture = to_sf_type(texture);
}

void SFMLRenderElement::setModelViewMatrix(
    htps::f32 const* const model_view_matrix)
{
    render_states_.transform = to_sf_type(model_view_matrix);
}

void SFMLRenderElement::setProjectionMatrix(
    htps::f32 const* const /*projection_matrix*/)
{}

void SFMLRenderElement::setShader(IShader const* const shader)
{
    render_states_.shader = to_sf_type(shader);
}

void SFMLRenderElement::render(sf::RenderTarget& target) const
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

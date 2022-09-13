#include "renderizable_private.hpp"

using namespace htps;
using namespace haf::scene;

namespace haf::render
{

Renderizable::RenderizablePrivate::RenderizablePrivate(
    size_type const num_vertex,
    FigType_t const figure_type,
    sptr<sys::RenderTarget> render_target) :
    figure_type_{figure_type},
    render_target_{htps::move(render_target)},
    m_render_element{}
{
    positions_.resize(num_vertex);
    colors_.resize(num_vertex);
    texture_coordinates_.resize(num_vertex);
    m_render_element.setSize(num_vertex);
    updatePositions();
}

void Renderizable::RenderizablePrivate::render()
{
    render_target_->draw(m_render_element);
}

void Renderizable::RenderizablePrivate::updatePositions()
{
    switch (figure_type_)
    {
        case FigType_t::Sprite:
        {
            setQuad(positions_);
        }
        break;

        case FigType_t::PolygonSprite:
        {
            setPolygon(positions_);
        }
        break;
    }
    m_render_element.setPositions(positions_.cbegin());
}

void Renderizable::RenderizablePrivate::updateTextureRect(
    htps::Rects32 const& textureRect)
{
    setTextureRect(positions_, texture_coordinates_, textureRect);
    m_render_element.setTexturecoordinates(texture_coordinates_.cbegin());
}

void Renderizable::RenderizablePrivate::updateColors(scene::Color const& color)
{
    setColor(colors_, color);
    m_render_element.setColors(colors_.cbegin());
}

}  // namespace haf::render

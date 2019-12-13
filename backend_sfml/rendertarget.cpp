#include <lib/scene/vertexarray.hpp>

#include "conversions.hpp"

#include <SFML/Config.hpp>

namespace lib::backend::sfmlb
{
    void RenderTarget::draw(
        const scene::Vertex *vertices,
        const u32 nVertex,
        const scene::PrimitiveType pType,
        const f32 *transform,
        const ITexture *texture,
        const IShader *shader)
    {
        sf::RenderTarget::draw((const sf::Vertex*)vertices, nVertex,
            static_cast<sf::PrimitiveType>(pType),
            to_sf_type(transform, texture, shader));
    }

    void RenderTarget::setViewPort(const Rectf32 & nviewport)
    {
        sf::View currentView(getView());
        currentView.setViewport(to_sf_type(nviewport));
        setView(currentView);
    }

    Rectf32 RenderTarget::viewPort() const
    {
        sf::View currentView(getView());
        return from_sft_type(currentView.getViewport());
    }

    void RenderTarget::setViewRect(const Rectf32 & nviewRect)
    {
        sf::View currentView(getView());
        currentView.setCenter(to_sf_type(nviewRect.center()));
        currentView.setSize(to_sf_type(nviewRect.size()));
        setView(currentView);
    }

    Rectf32 RenderTarget::viewRect() const
    {
        sf::View currentView(getView());
        return rectFromCenterAndSize(from_sf_type(currentView.getCenter()), from_sf_type(currentView.getSize()));
    }

    void RenderTarget::clear()
    {
        sf::RenderTarget::clear();
    }
}

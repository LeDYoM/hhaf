#include "rendertarget.hpp"
#include "conversions.hpp"
#include "render_element.hpp"
#include <backend_dev/include/ivertex.hpp>

#include <SFML/Config.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
static_assert(sizeof(sf::Vertex) == sizeof(iVertex),
              "Incomptable version of SFML");

RenderTarget::~RenderTarget() = default;

void RenderTarget::initialize()
{
    sf::RenderTarget::initialize();
}

void RenderTarget::render(IRenderElement const** render_element_begin,
                          IRenderElement const** const render_element_end)
{
    while (render_element_begin != render_element_end)
    {
        auto const* const r{
            dynamic_cast<RenderElement const* const>(*render_element_begin++)};
        sf::RenderTarget::draw(
            &(r->nativeVertexArray()[0U]),
            r->nativeVertexArray().getVertexCount(),
            r->nativeVertexArray().getPrimitiveType(),
            r->nativeRenderStates());
    }
}

void RenderTarget::setViewPort(const Rectf32& nviewport)
{
    sf::View currentView(getView());
    currentView.setViewport(to_sf_type(nviewport));
    setView(currentView);
}

Rectf32 RenderTarget::viewPort() const
{
    sf::View currentView(getView());
    return from_sf_type(currentView.getViewport());
}

void RenderTarget::setViewRect(const Rectf32& nviewRect)
{
    sf::View currentView(getView());
    currentView.setCenter(to_sf_type(nviewRect.center()));
    currentView.setSize(to_sf_type(nviewRect.size()));
    setView(currentView);
}

Rectf32 RenderTarget::viewRect() const
{
    sf::View currentView(getView());
    return rectFromCenterAndSize(from_sf_type(currentView.getCenter()),
                                 from_sf_type(currentView.getSize()));
}

void RenderTarget::clear()
{
    sf::RenderTarget::clear();
}

htps::str RenderTarget::info() const
{
    return make_str(
        "name:SFMLWindowRenderTargget;provider:SFML;provider_version:",
        SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".", SFML_VERSION_PATCH,
        ";version:0;subversion:2:patch3");
}

sf::Vector2u RenderTarget::getSize() const
{
    return sf::Vector2u{};
}

IRenderElement* RenderTarget::createRenderElement()
{
    return new RenderElement();
}

bool RenderTarget::destroyRenderElement(IRenderElement* render_element)
{
    if (render_element != nullptr)
    {
        if (auto* casted_render_element{
                dynamic_cast<RenderElement*>(render_element)};
            render_element != nullptr)
        {
            delete casted_render_element;
            return true;
        }
    }
    return false;
}

}  // namespace haf::backend::sfmlb

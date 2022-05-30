#include "sfml_rendertarget.hpp"
#include "conversions.hpp"
#include "render_element.hpp"

#include <SFML/Config.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
SFMLRenderTarget::~SFMLRenderTarget() = default;

void SFMLRenderTarget::initialize()
{
    sf::RenderTarget::initialize();
}

void SFMLRenderTarget::drawDebugQuad([
    [maybe_unused]] IRenderElement const* const irender_element)
{
#ifdef DRAW_DEBUG_QUAD
    auto const* const render_element{
        static_cast<RenderElement const* const>(irender_element)};

    using namespace ::sf;
    VertexArray nva(sf::PrimitiveType::LineStrip, 5U);
    auto const bounds{render_element->nativeVertexArray().getBounds()};
    nva[0U] = {{bounds.left, bounds.top}, Color::Green};
    nva[1U] = {{bounds.left + bounds.width, bounds.top}, Color::Green};
    nva[2U] = {{bounds.left + bounds.width, bounds.top + bounds.width},
               Color::Green};
    nva[3U] = {{bounds.left, bounds.top + bounds.width}, Color::Green};
    nva[4U] = {{bounds.left, bounds.top}, sf::Color::Green};
    RenderTarget::draw(nva, render_element->nativeRenderStates().transform);
#endif
}

void SFMLRenderTarget::render(IRenderElement const* const render_element)
{
    renderImpl(static_cast<RenderElement const* const>(render_element));
}

void SFMLRenderTarget::render(
    IRenderElement const* const* render_element_begin,
    IRenderElement const* const* const render_element_end)
{
    while (render_element_begin != render_element_end)
    {
        render(*render_element_begin++);
    }
}

void SFMLRenderTarget::renderImpl(RenderElement const* const render_element)
{
    render_element->render(*this);
#ifdef DRAW_DEBUG_QUAD
    drawDebugQuad(render_element);
#endif
}

void SFMLRenderTarget::setViewPort(const Rectf32&)
{
    sf::View currentView(getView());
    currentView.setViewport(sf::FloatRect{0.0F, 0.0F, 1.0F, 1.0F});
    setView(currentView);
}

Rectf32 SFMLRenderTarget::viewPort() const
{
    sf::View currentView(getView());
    return from_sf_type(currentView.getViewport());
}

void SFMLRenderTarget::updateCamera(CameraData const& camera_data)
{
    if (camera_data.update_required)
    {
        sf::View view{to_sf_type(camera_data.nearRect)};
        view.setViewport(to_sf_type(camera_data.viewPort));
        sf::RenderTarget::setView(view);
    }
}

void SFMLRenderTarget::clear()
{
    sf::RenderTarget::clear();
}

htps::str SFMLRenderTarget::info() const
{
    return make_str(
        "name:SFMLWindowRenderTargget;provider:SFML;provider_version:",
        SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".", SFML_VERSION_PATCH,
        ";version:0;subversion:2:patch3");
}

sf::Vector2u SFMLRenderTarget::getSize() const
{
    return sf::Vector2u{};
}

IRenderElement* SFMLRenderTarget::createRenderElement()
{
    return new RenderElement();
}

bool SFMLRenderTarget::destroyRenderElement(IRenderElement* render_element)
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

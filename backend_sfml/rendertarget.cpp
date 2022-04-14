#include "rendertarget.hpp"
#include "conversions.hpp"
#include "render_element.hpp"
#include "camera.hpp"

#include <SFML/Config.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
RenderTarget::~RenderTarget() = default;

void RenderTarget::initialize()
{
    sf::RenderTarget::initialize();
}

void RenderTarget::drawDebugQuad([
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

void RenderTarget::render(IRenderElement const* const render_element)
{
    renderImpl(static_cast<RenderElement const*const>(render_element));
}

void RenderTarget::render(IRenderElement const** render_element_begin,
                          IRenderElement const** const render_element_end)
{
    while (render_element_begin != render_element_end)
    {
        auto const* const render_element{
            static_cast<IRenderElement const* const>(*render_element_begin++)};
        render(render_element);
    }
}

void RenderTarget::renderImpl(RenderElement const* render_element)
{
        render_element->render(*this);
#ifdef DRAW_DEBUG_QUAD
        drawDebugQuad(render_element);
#endif
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

void RenderTarget::updateCamera(ICamera* const camera)
{
    if (camera->updateRequired())
    {
        Camera* const camera_sf{to_sf_type(camera)};
        setView(camera_sf->getView());
        camera_sf->resetUpdateRequired();
    }
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

ICamera* RenderTarget::createCamera()
{
    return new Camera();
}

bool RenderTarget::destroyCamera(ICamera* camera)
{
    if (camera != nullptr)
    {
        if (auto d_camera{dynamic_cast<Camera*>(camera)}; d_camera != nullptr)
        {
            delete d_camera;
            return true;
        }
    }
    return false;
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

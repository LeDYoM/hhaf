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

void RenderTarget::render(IRenderElement const** render_element_begin,
                          IRenderElement const** const render_element_end)
{
    while (render_element_begin != render_element_end)
    {
        auto const* const r{
            static_cast<RenderElement const* const>(*render_element_begin++)};
        sf::RenderTarget::draw(r->nativeVertexArray(), r->nativeRenderStates());
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

void RenderTarget::updateCamera(ICamera* camera)
{
    if (camera->updateRequired())
    {
        Camera* camera_sf{to_sf_type(camera)};
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
        return true;
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

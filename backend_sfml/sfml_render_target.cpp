#include "sfml_render_target.hpp"
#include "conversions.hpp"
#include "sfml_render_element.hpp"

#include <SFML/Config.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
SFMLRenderTarget::~SFMLRenderTarget() = default;

void SFMLRenderTarget::setInternalRenderTarget(sf::RenderTarget* render_target)
{
    m_render_target = render_target;
}

void SFMLRenderTarget::drawDebugQuad([
    [maybe_unused]] IRenderElement const* const irender_element)
{
#ifdef DRAW_DEBUG_QUAD
    auto const* const render_element{
        static_cast<SFMLRenderElement const* const>(
            irender_element)};

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
    renderImpl(static_cast<SFMLRenderElement const* const>(
        render_element));
}

void SFMLRenderTarget::render(
    rptr<CameraData const> const camera_data,
    htps::span<IRenderElement const* const> const& render_element_span)
{
    if (camera_data != nullptr)
    {
        updateCamera(*camera_data);
    }

    for (auto&& render_element : render_element_span)
    {
        render(render_element);
    }
}

void SFMLRenderTarget::renderImpl(
    SFMLRenderElement const* const render_element)
{
    render_element->render(*m_render_target);
#ifdef DRAW_DEBUG_QUAD
    drawDebugQuad(render_element);
#endif
}

void SFMLRenderTarget::forceCameraUpdate()
{
    m_force_camera_update = true;
}

void SFMLRenderTarget::updateCamera(CameraData const& camera_data)
{
    if (camera_data.update_required || m_force_camera_update)
    {
        sf::View view{to_sf_type(camera_data.nearRect)};
        view.setViewport(to_sf_type(camera_data.viewPort));
        m_render_target->setView(view);
        m_force_camera_update = false;
    }
}

void SFMLRenderTarget::clear()
{
    m_render_target->clear();
}

htps::str SFMLRenderTarget::info() const
{
    return make_str(
        "name:SFMLwRenderTarget;provider:SFML;provider_version:",
        SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".", SFML_VERSION_PATCH,
        ";version:0;subversion:3:patch0");
}

sf::Vector2u SFMLRenderTarget::getSize() const
{
    return sf::Vector2u{};
}

IRenderElement* SFMLRenderTarget::createRenderElement()
{
    return new SFMLRenderElement();
}

}  // namespace haf::backend::sfmlb

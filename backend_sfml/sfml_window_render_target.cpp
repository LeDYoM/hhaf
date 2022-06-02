#include "sfml_window_render_target.hpp"
#include "conversions.hpp"
#include "sfml_render_element.hpp"

#include <SFML/Config.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
SFMLWindowRenderTarget::SFMLWindowRenderTarget(
    sf::RenderWindow& render_window) :
    m_render_window{render_window}
{}

SFMLWindowRenderTarget::~SFMLWindowRenderTarget() = default;

htps::str SFMLWindowRenderTarget::info() const
{
    return make_str(
        "name:SFMLWindowRenderTarget;provider:SFML;provider_version:",
        SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".", SFML_VERSION_PATCH,
        ";version:0;subversion:2:patch3");
}

IRenderElement* SFMLWindowRenderTarget::createRenderElement()
{
    return new SFMLRenderElement();
}

sf::RenderTarget& SFMLWindowRenderTarget::internalRenderTarget()
{
    return m_render_window;
}

}  // namespace haf::backend::sfmlb

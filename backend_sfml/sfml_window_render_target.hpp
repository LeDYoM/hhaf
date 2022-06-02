#ifndef HAF_BACKEND_SFMLB_WINDOW_RENDERTARGET_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_WINDOW_RENDERTARGET_INCLUDE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <backend_dev/include/irendertarget.hpp>
#include <backend_dev/include/irender_element.hpp>
#include "sfml_render_target.hpp"

namespace haf::backend::sfmlb
{
class SFMLRenderElement;

class SFMLWindowRenderTarget : public SFMLRenderTarget
//    : public IRenderTarget
{
public:
    explicit SFMLWindowRenderTarget(sf::RenderWindow& render_window);
    ~SFMLWindowRenderTarget() override;

    htps::str info() const override;
    IRenderElement* createRenderElement() override;

private:
    sf::RenderTarget& internalRenderTarget() override;
    sf::RenderWindow& m_render_window;
};
}  // namespace haf::backend::sfmlb

#endif

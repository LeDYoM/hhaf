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

    void render(htps::rptr<CameraData const> const camera_data,
                htps::span<IRenderElement const* const> const&
                    render_element_span) override;

    void clear() override;
    void forceCameraUpdate() override;

    htps::str info() const override;
    IRenderElement* createRenderElement() override;

private:
    sf::RenderTarget& internalRenderTarget() override;
    sf::RenderWindow& m_render_window;
    void updateCamera(CameraData const&);
    void drawDebugQuad(IRenderElement const* const irender_element);
    bool m_force_camera_update{false};
};
}  // namespace haf::backend::sfmlb

#endif

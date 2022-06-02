#ifndef HAF_BACKEND_SFMLB_WINDOW_RENDERTARGET_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_WINDOW_RENDERTARGET_INCLUDE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <backend_dev/include/irendertarget.hpp>
#include <backend_dev/include/irender_element.hpp>

namespace haf::backend::sfmlb
{
class SFMLRenderElement;

class SFMLWindowRenderTarget : public IRenderTarget
{
public:
    explicit SFMLWindowRenderTarget(sf::RenderWindow& render_window);
    ~SFMLWindowRenderTarget() override;

    void render(htps::rptr<CameraData const> const camera_data,
                htps::span<IRenderElement const* const> const&
                    render_element_span) override;

    void render(IRenderElement const* render_element);
    void clear() override;
    void forceCameraUpdate() override;

    htps::str info() const override;
    IRenderElement* createRenderElement() override;

private:
    sf::RenderWindow& m_render_window;
    void updateCamera(CameraData const&);
    void renderImpl(SFMLRenderElement const* const render_element);
    void drawDebugQuad(IRenderElement const* const irender_element);
    bool m_force_camera_update{false};
};
}  // namespace haf::backend::sfmlb

#endif

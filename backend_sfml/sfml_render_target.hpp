#ifndef HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <backend_dev/include/irendertarget.hpp>
#include <backend_dev/include/irender_element.hpp>

namespace haf::backend::sfmlb
{
class SFMLRenderElement;

class SFMLRenderTarget : public IRenderTarget, private sf::RenderTarget
{
public:
    ~SFMLRenderTarget() override;

    void render(htps::rptr<CameraData const> const camera_data,
                htps::span<IRenderElement const* const> const&
                    render_element_span) override;

    void render(IRenderElement const* render_element);
    void clear() override;
    void forceCameraUpdate() override;

    htps::str info() const override;
    sf::Vector2u getSize() const override;

    IRenderElement* createRenderElement() override;

private:
    void updateCamera(CameraData const&);
    void renderImpl(SFMLRenderElement const* const render_element);
    void drawDebugQuad(IRenderElement const* const irender_element);
    bool m_force_camera_update{false};
};
}  // namespace haf::backend::sfmlb

#endif

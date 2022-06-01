#ifndef HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <backend_dev/include/irendertarget.hpp>
#include <backend_dev/include/irender_element.hpp>

namespace haf::backend::sfmlb
{
class RenderElement;

class SFMLRenderTarget : public IRenderTarget, public sf::RenderTarget
{
public:
    ~SFMLRenderTarget() override;
    void initialize() override;

    void render(htps::rptr<CameraData const> const camera_data,
                htps::span<IRenderElement const* const> const&
                    render_element_span) override;

    void render(IRenderElement const* render_element);
    void renderImpl(RenderElement const* const render_element);

    void updateCamera(CameraData const&);
    void clear() override;
    void forceCameraUpdate() override;

    htps::str info() const override;
    sf::Vector2u getSize() const override;

    IRenderElement* createRenderElement() override;
    bool destroyRenderElement(IRenderElement* render_element) override;

private:
    void drawDebugQuad(IRenderElement const* const irender_element);
    bool m_force_camera_update{false};
};
}  // namespace haf::backend::sfmlb

#endif

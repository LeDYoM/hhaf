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

class SFMLRenderTarget : public IRenderTarget
{
public:
    ~SFMLRenderTarget() override;

    void setInternalRenderTarget(sf::RenderTarget* render_target);

    void render(htps::rptr<CameraData const> const camera_data,
                htps::span<IRenderElement const* const> const&
                    render_element_span) override;

    void render(IRenderElement const* render_element);

    htps::str info() const override;
    htps::uptr<IRenderElement> createRenderElement() override;
private:
    sf::RenderTarget* m_render_target{nullptr};
    void updateCamera(CameraData const&);
    void renderImpl(SFMLRenderElement const* const render_element);
    void drawDebugQuad(IRenderElement const* const irender_element);
};
}  // namespace haf::backend::sfmlb

#endif

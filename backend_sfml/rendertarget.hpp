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

class RenderTarget : public IRenderTarget, public sf::RenderTarget
{
public:
    ~RenderTarget() override;
    void initialize() override;

    void render(IRenderElement const** render_element_begin,
                IRenderElement const** const render_element_end) override;

    void render(IRenderElement const* render_element);
    void renderImpl(RenderElement const* render_element);

    void setViewPort(const htps::Rectf32& nviewport) override;
    htps::Rectf32 viewPort() const override;

    void updateCamera(ICamera* const) override;
    void clear() override;

    htps::str info() const override;
    sf::Vector2u getSize() const override;

    ICamera* createCamera() override;
    bool destroyCamera(ICamera* camera) override;

    IRenderElement* createRenderElement() override;
    bool destroyRenderElement(IRenderElement* render_element) override;
private:
    void drawDebugQuad(IRenderElement const* const irender_element);
};
}  // namespace haf::backend::sfmlb

#endif

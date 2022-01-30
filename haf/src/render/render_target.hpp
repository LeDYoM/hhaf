#ifndef HAF_CORE_RENDER_TARGET_INCLUDE_HPP
#define HAF_CORE_RENDER_TARGET_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>

namespace haf::backend
{
class IRenderTarget;
class IRenderElement;
}  // namespace haf::backend

namespace haf::render
{
class RenderData;
}

namespace haf::sys
{
/**
 * @brief Class to encapsulate a Render target from the render target interface.
 *
 * This class is to be used to export the functionality of the render target
 * interface into a concrete class.
 */
class RenderTarget
{
public:
    /**
     * @brief Construct a new RenderTarget object
     *
     * @param renderTarget Interface to the underlying low level render target.
     */
    RenderTarget(htps::rptr<backend::IRenderTarget> renderTarget);

    /**
     * @brief Destroy the Render Target object
     */
    ~RenderTarget();

    void setViewPort(const htps::Rectf32& nviewport);
    htps::Rectf32 viewPort() const;
    void setViewRect(const htps::Rectf32& nviewRect);
    htps::Rectf32 viewRect() const;

    void draw(htps::rptr<backend::IRenderElement const> render_element);
    void update();
    void clearRenderQueue();

    void clear();

    backend::IRenderElement* createRenderElement();
    bool destroyRenderElement(backend::IRenderElement* render_element);

private:
    htps::rptr<backend::IRenderTarget> irender_target_;
    htps::vector<htps::rptr<backend::IRenderElement const>>
        render_element_container_;
};
}  // namespace haf::sys

#endif

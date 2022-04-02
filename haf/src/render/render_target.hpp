#ifndef HAF_CORE_RENDER_TARGET_INCLUDE_HPP
#define HAF_CORE_RENDER_TARGET_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>

namespace haf::backend
{
class IRenderTarget;
class IRenderElement;
class ICamera;
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

    void draw(htps::rptr<backend::ICamera> camera);
    void draw(htps::rptr<backend::IRenderElement const> render_element);
    void update();
    void clearRenderQueue();

    void clear();

    backend::IRenderElement* createRenderElement();
    bool destroyRenderElement(backend::IRenderElement* render_element);
    backend::ICamera* createCamera();
    bool destroyCamera(backend::ICamera* camera);

private:
    htps::rptr<backend::IRenderTarget> irender_target_;
    htps::rptr<backend::ICamera> icamera_;
    htps::vector<htps::rptr<backend::IRenderElement const>>
        render_element_container_;
};
}  // namespace haf::sys

#endif

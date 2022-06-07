HTPS_PRAGMA_ONCE
#ifndef HAF_CORE_RENDER_TARGET_INCLUDE_HPP
#define HAF_CORE_RENDER_TARGET_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <backend_dev/include/camera_data.hpp>
#include <backend_dev/include/irender_element.hpp>

namespace haf::backend
{
class IRenderTarget;
}  // namespace haf::backend

namespace haf::render
{
class RenderData;
class RenderElement;
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

    void draw(backend::CameraData const& camera_data);
    void draw(render::RenderElement const& render_element);
    void update();
    void clearRenderQueue();

    htps::uptr<backend::IRenderElement> createRenderElement();

private:
    htps::rptr<backend::IRenderTarget> irender_target_;
    backend::CameraData m_camera_data;
    htps::vector<htps::rptr<backend::IRenderElement const>>
        render_element_container_;
};
}  // namespace haf::sys

#endif

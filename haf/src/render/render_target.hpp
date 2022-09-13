HTPS_PRAGMA_ONCE
#ifndef HAF_CORE_RENDER_TARGET_INCLUDE_HPP
#define HAF_CORE_RENDER_TARGET_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/properties/property_state.hpp>
#include <haf/include/scene/matrix4x4.hpp>

namespace haf::ogl
{
class RenderTarget;
class RenderElement;
}  // namespace haf::ogl

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
     */
    RenderTarget();

    void draw(ogl::RenderElement const& render_element);
    void update();
    void clearRenderQueue();

    htps::PropertyState<htps::Rects32> ViewPort;
    htps::PropertyState<scene::Matrix4x4> Projection;

private:
    htps::sptr<ogl::RenderTarget> irender_target_;
    htps::vector<htps::rptr<ogl::RenderElement const>>
        render_element_container_;
};
}  // namespace haf::sys

#endif

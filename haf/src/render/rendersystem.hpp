#ifndef HAF_SYS_SYSTEM_RENDERSYSTEM_INCLUDE_HPP
#define HAF_SYS_SYSTEM_RENDERSYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include "rendertarget.hpp"
#include <haf/include/render/renderdata.hpp>

#include "system/systembase.hpp"

namespace haf::scene
{
class RenderData;
}

namespace haf::sys
{
class RenderTarget;

/**
 * @brief This system is intended to be the responsible of
 * priving the render data to the Backend render part.
 */
class RenderSystem final : public SystemBase
{
public:
    using SystemBase::SystemBase;
    void update();

    void draw(const render::RenderData& renderData);
    void clear();

    void setRenderTarget(htps::sptr<RenderTarget> render_target);
    void clearRenderQueue();

private:
    htps::sptr<RenderTarget> render_target_;
    htps::vector<render::RenderData> render_data_container_;
};
}  // namespace haf::sys

#endif

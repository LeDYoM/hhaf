#pragma once

#ifndef HAF_SYS_SYSTEM_RENDERSYSTEM_INCLUDE_HPP
#define HAF_SYS_SYSTEM_RENDERSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <system/i_include/appservice.hpp>
#include "rendertarget.hpp"
#include <haf/render/include/renderdata.hpp>

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
class RenderSystem final : public AppService
{
public:
    using AppService::AppService;
    void update();

    void draw(const scene::RenderData &renderData);
    void clear();

    void setRenderTarget(mtps::sptr<RenderTarget> render_target);
    void clearRenderQueue();

private:
    mtps::sptr<RenderTarget> render_target_;
    mtps::vector<scene::RenderData> render_data_container_;
};
} // namespace haf::sys

#endif

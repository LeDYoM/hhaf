#pragma once

#ifndef LIB_SYS_SYSTEM_RENDERSYSTEM_INCLUDE_HPP
#define LIB_SYS_SYSTEM_RENDERSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/include/appservice.hpp>

namespace lib::scene
{
class RenderData;
}

namespace lib::sys
{
class RenderTarget;

/**
* This system is intended to be the responsible of
* priving the render data to the Backend render part.
*/
class RenderSystem final : public AppService
{
public:
    RenderSystem(sys::SystemProvider &system_provider);
    ~RenderSystem() override;

    void update();

    void draw(const scene::RenderData &renderData);
    void clear();

    void setRenderTarget(mtps::sptr<RenderTarget> render_target);

private:
    struct RenderSystemPrivate;
    mtps::uptr<RenderSystemPrivate> priv_;
};
} // namespace lib::sys

#endif

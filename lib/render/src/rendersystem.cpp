#include "rendersystem.hpp"
#include <lib/render/include/rendertarget.hpp>
#include <lib/render/include/renderdata.hpp>
#include <lib/include/liblog.hpp>

#include <mtypes/include/types.hpp>

namespace lib::sys
{
struct RenderSystem::RenderSystemPrivate final
{
    sptr<RenderTarget> render_target_;
};

RenderSystem::RenderSystem(sys::SystemProvider &system_provider)
    : AppService{system_provider},
      priv_{muptr<RenderSystemPrivate>()}
{
}

RenderSystem::~RenderSystem() = default;

void RenderSystem::update()
{
}

void RenderSystem::draw(const scene::RenderData &renderData)
{
    priv_->render_target_->draw(renderData);
}

void RenderSystem::clear()
{
    priv_->render_target_->clear();
}

void RenderSystem::setRenderTarget(sptr<RenderTarget> render_target)
{
    log_assert(render_target != nullptr, "Parameter is nullptr");
    log_assert(priv_->render_target_ == nullptr, 
        "Render target was already set");

    priv_->render_target_ = std::move(render_target);
}

} // namespace lib::sys

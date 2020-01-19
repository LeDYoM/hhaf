#include <lib/render/include/rendersystem.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/system/window.hpp>
#include <lib/render/include/rendertarget.hpp>
#include <lib/scene/renderdata.hpp>

#include <mtypes/include/types.hpp>

namespace lib::sys
{
struct RenderSystem::RenderSystemPrivate final
{
    RenderSystemPrivate(rptr<RenderTarget> render_target) noexcept 
        : render_target_{std::move(render_target)} {}
    ~RenderSystemPrivate() {}
    const rptr<RenderTarget> render_target_;
};

RenderSystem::RenderSystem(sys::SystemProvider &system_provider)
    : HostedAppService{system_provider},
      priv_{muptr<RenderSystemPrivate>(
          system_provider.parentWindow().renderTarget().get())}
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
} // namespace lib::sys

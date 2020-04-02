#include "rendersystem.hpp"
#include <lib/render/include/rendertarget.hpp>
#include <lib/render/include/renderdata.hpp>
#include <lib/include/liblog.hpp>

#include <mtypes/include/types.hpp>

namespace lib::sys
{
struct RenderSystem::RenderSystemPrivate final
{
    mtps::sptr<RenderTarget> render_target_;
    mtps::vector<scene::RenderData> render_data_container_;
};

RenderSystem::RenderSystem(sys::SystemProvider &system_provider)
    : AppService{system_provider},
      priv_{mtps::muptr<RenderSystemPrivate>()}
{
}

RenderSystem::~RenderSystem() = default;

void RenderSystem::update()
{
    for (const auto& render_data : priv_->render_data_container_)
    {
        priv_->render_target_->draw(render_data);
    }
    priv_->render_data_container_.clear();
}

void RenderSystem::draw(const scene::RenderData &renderData)
{
    priv_->render_target_->draw(renderData);
    priv_->render_data_container_.push_back(renderData);
}

void RenderSystem::clear()
{
    priv_->render_target_->clear();
}

void RenderSystem::setRenderTarget(mtps::sptr<RenderTarget> render_target)
{
    log_assert(render_target != nullptr, "Parameter is nullptr");
    log_assert(priv_->render_target_ == nullptr, 
        "Render target was already set");

    priv_->render_target_ = std::move(render_target);
}

void RenderSystem::clearRenderQueue()
{
    priv_->render_data_container_.clear();
}

} // namespace lib::sys

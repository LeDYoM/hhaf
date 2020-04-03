#include "rendersystem.hpp"
#include <lib/render/include/rendertarget.hpp>
#include <lib/render/include/renderdata.hpp>
#include <lib/include/liblog.hpp>

#include <mtypes/include/types.hpp>

using namespace mtps;
namespace lib::sys
{
struct RenderSystem::RenderSystemPrivate final
{
    mtps::sptr<RenderTarget> render_target_;
    mtps::vector<scene::RenderData> render_data_container_;

    void update()
    {
        render_target_->drawBatch(render_data_container_.cbegin(),
                                  render_data_container_.cend());
        render_data_container_.clear();
    }
};

RenderSystem::RenderSystem(sys::SystemProvider& system_provider) :
    AppService{system_provider}, priv_{mtps::muptr<RenderSystemPrivate>()}
{}

RenderSystem::~RenderSystem() = default;

void RenderSystem::update()
{
    priv_->update();
}

void RenderSystem::draw(const scene::RenderData& renderData)
{
//    priv_->render_target_->draw(renderData);
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

}  // namespace lib::sys

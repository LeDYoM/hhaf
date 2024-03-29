#include "render_system.hpp"
#include "render_target.hpp"
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::sys
{

void RenderSystem::update()
{
    render_target_->update();
    render_target_->clearRenderQueue();
}

void RenderSystem::setRenderTarget(sptr<RenderTarget> render_target)
{
    LogAsserter::log_assert(render_target != nullptr, "Parameter is nullptr");
    LogAsserter::log_assert(render_target_ == nullptr,
                            "Render target was already set");

    render_target_ = htps::move(render_target);
}

sptr<RenderTarget> const& RenderSystem::currentRenderTarget() const
{
    return render_target_;
}

}  // namespace haf::sys

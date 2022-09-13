#include "render_system.hpp"
#include "render_target.hpp"
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::sys
{
void RenderSystem::initialize()
{
    render_target_ = msptr<RenderTarget>();
}

void RenderSystem::update()
{
    render_target_->update();
    render_target_->clearRenderQueue();
}

sptr<RenderTarget> const& RenderSystem::currentRenderTarget() const
{
    return render_target_;
}

}  // namespace haf::sys

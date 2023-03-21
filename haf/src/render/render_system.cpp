#include "render_system.hpp"
#include "render_target.hpp"
#include <hlog/include/hlog.hpp>
#include <hogl/include/render_system_functions.hpp>

using namespace htps;

namespace haf::sys
{
void RenderSystem::initialize(bool const enableDebug)
{
    m_initialized = ogl::initOGL();
    LogAsserter::log_assert(m_initialized == true);
    ogl::setDebug(enableDebug);
    ogl::setDefaultRenderState();
}

void RenderSystem::update()
{
//    render_target_->update();
//    render_target_->clearRenderQueue();
}

sptr<RenderTarget> const& RenderSystem::currentRenderTarget() const
{
    return render_target_;
}

}  // namespace haf::sys

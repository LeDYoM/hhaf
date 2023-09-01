#include "render_system.hpp"
#include "render_target.hpp"
#include <hlog/include/hlog.hpp>
#include <hogl/include/render_system_functions.hpp>

using namespace haf::core;
using namespace haf::render;

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
}

void RenderSystem::finish()
{
}

sptr<RenderTarget> const& RenderSystem::currentRenderTarget() const
{
    return render_target_;
}

SharedDataManager& RenderSystem::sharedDataManager() noexcept
{
    return m_shared_data_manager;
}

SharedDataManager const& RenderSystem::sharedDataManager() const noexcept
{
    return m_shared_data_manager;
}

void RenderSystem::beginFrame(fmath::vector4df const& backgroundColor)
{
    ogl::clearBackgroundColor(backgroundColor);
    ogl::clearDepthBuffer();
}

void RenderSystem::endFrame()
{}

}  // namespace haf::sys

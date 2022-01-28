#include "render_system.hpp"
#include "render_target.hpp"
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::sys
{

void RenderSystem::update()
{
    render_target_->render(render_element_container_.begin(),
                           render_element_container_.end());
    clearRenderQueue();
}

void RenderSystem::draw(backend::IRenderElement const* render_element)
{
    render_element_container_.push_back(render_element);
}

void RenderSystem::clear()
{
    render_target_->clear();
}

void RenderSystem::setRenderTarget(sptr<RenderTarget> render_target)
{
    LogAsserter::log_assert(render_target != nullptr, "Parameter is nullptr");
    LogAsserter::log_assert(render_target_ == nullptr,
                            "Render target was already set");

    render_target_ = std::move(render_target);
}

void RenderSystem::clearRenderQueue()
{
    render_element_container_.clear();
}

backend::IRenderElement* RenderSystem::createRenderElement()
{
    return render_target_->createRenderElement();
}

bool RenderSystem::destroyRenderElement(backend::IRenderElement* render_element)
{
    return render_target_->destroyRenderElement(render_element);
}

}  // namespace haf::sys

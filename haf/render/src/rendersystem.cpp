#include <render/i_include/rendersystem.hpp>
#include <haf/render/include/renderdata.hpp>
#include <hlog/include/hlog.hpp>

#include <htypes/include/types.hpp>

using namespace mtps;

namespace haf::sys
{

void RenderSystem::update()
{
    render_target_->render(render_data_container_.cbegin(),
                           render_data_container_.cend());
    render_data_container_.clear();
}

void RenderSystem::draw(const scene::RenderData& renderData)
{
    render_data_container_.push_back(renderData);
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
    render_data_container_.clear();
}

}  // namespace haf::sys

#include "render_target.hpp"

#include <backend_dev/include/irendertarget.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::sys
{
RenderTarget::RenderTarget(rptr<haf::backend::IRenderTarget> renderTarget) :
    irender_target_{htps::move(renderTarget)},
    m_camera_data{},
    render_element_container_{}
{
    LogAsserter::log_assert(renderTarget != nullptr,
                            "renderTarget parameter is nullptr");
}

RenderTarget::~RenderTarget() = default;

void RenderTarget::draw(
    htps::rptr<backend::IRenderElement const> render_element)
{
    render_element_container_.push_back(render_element);
}

void RenderTarget::draw(backend::CameraData const& camera_data)
{
    m_camera_data = camera_data;
}

void RenderTarget::update()
{
    irender_target_->updateCamera(m_camera_data);

    irender_target_->render(render_element_container_.begin(),
                            render_element_container_.end());
}

void RenderTarget::clear()
{
    irender_target_->clear();
}

void RenderTarget::clearRenderQueue()
{
    render_element_container_.clear();
}

backend::IRenderElement* RenderTarget::createRenderElement()
{
    return irender_target_->createRenderElement();
}

bool RenderTarget::destroyRenderElement(backend::IRenderElement* render_element)
{
    return irender_target_->destroyRenderElement(render_element);
}

}  // namespace haf::sys

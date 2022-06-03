#include "render_target.hpp"

#include <htypes/include/span.hpp>
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

void RenderTarget::draw(
    htps::rptr<backend::IRenderElement const> render_element)
{
    render_element_container_.push_back(render_element);
}

void RenderTarget::draw(backend::CameraData const& camera_data)
{
    if (camera_data.update_required)
    {
        m_camera_data = camera_data;
    }
    else
    {
        m_camera_data.update_required = false;
    }
}

void RenderTarget::update()
{
    irender_target_->render(&m_camera_data,
                            make_const_span(render_element_container_));
}

void RenderTarget::clearRenderQueue()
{
    render_element_container_.clear();
}

backend::IRenderElement* RenderTarget::createRenderElement()
{
    return irender_target_->createRenderElement();
}

}  // namespace haf::sys

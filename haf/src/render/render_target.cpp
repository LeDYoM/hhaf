#include "render_target.hpp"

#include <backend_dev/include/irendertarget.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::sys
{
RenderTarget::RenderTarget(rptr<haf::backend::IRenderTarget> renderTarget) :
    irender_target_{std::move(renderTarget)}, icamera_{nullptr}
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

void RenderTarget::draw(htps::rptr<backend::ICamera> camera)
{
    icamera_ = camera;
}

void RenderTarget::update()
{
    if (icamera_)
    {
        irender_target_->updateCamera(icamera_);
    }

    irender_target_->render(render_element_container_.begin(),
                            render_element_container_.end());
    icamera_ = nullptr;
}

void RenderTarget::clear()
{
    irender_target_->clear();
}

void RenderTarget::clearRenderQueue()
{
    render_element_container_.clear();
    icamera_ = nullptr;
}

Rectf32 RenderTarget::viewPort() const
{
    return irender_target_->viewPort();
}

void RenderTarget::setViewPort(const Rectf32& nViewPort)
{
    irender_target_->setViewPort(nViewPort);
}

Rectf32 RenderTarget::viewRect() const
{
    return irender_target_->viewRect();
}

void RenderTarget::setViewRect(const Rectf32& nViewRect)
{
    irender_target_->setViewRect(nViewRect);
}

backend::IRenderElement* RenderTarget::createRenderElement()
{
    return irender_target_->createRenderElement();
}

bool RenderTarget::destroyRenderElement(backend::IRenderElement* render_element)
{
    return irender_target_->destroyRenderElement(render_element);
}

backend::ICamera* RenderTarget::createCamera()
{
    return irender_target_->createCamera();
}

bool RenderTarget::destroyCamera(backend::ICamera* camera)
{
    return irender_target_->destroyCamera(camera);
}

}  // namespace haf::sys

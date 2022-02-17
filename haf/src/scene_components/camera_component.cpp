#include <haf/include/scene_components/camera_component.hpp>
#include <backend_dev/include/icamera.hpp>
#include "render/render_system.hpp"
#include "render/render_target.hpp"
#include "system/get_system.hpp"

using namespace haf::types;

namespace haf::scene
{
struct CameraComponent::CameraComponentPrivate
{
    htps::rptr<backend::ICamera> icamera_{nullptr};
    htps::sptr<sys::RenderTarget> render_target_;

    void draw() { render_target_->draw(icamera_); }

    bool destroyCamera()
    {
        if (render_target_ != nullptr && icamera_ != nullptr)
        {
            return render_target_->destroyCamera(icamera_);
        }
        return false;
    }
};

CameraComponent::CameraComponent() : p_{make_pimplp<CameraComponentPrivate>()}
{}

CameraComponent::~CameraComponent()
{
    (void)(p_->destroyCamera());
}

void CameraComponent::onAttached()
{
    p_->render_target_ =
        sys::getSystem<sys::RenderSystem>(attachedNode()).currentRenderTarget();
    p_->icamera_ = p_->render_target_->createCamera();

    view     = decltype(view)::value_type{{0, 0}, {1000, 1000}};
    viewPort = decltype(viewPort)::value_type{{0, 0}, {1, 1}};
}

void CameraComponent::moveView(SceneCoordinates const& delta)
{
    view = view() + delta;
}

void CameraComponent::update()
{
    if (view.readResetHasChanged())
    {
        p_->icamera_->setFarRect(view());
    }

    if (viewPort.readResetHasChanged())
    {
        p_->icamera_->setViewPort(viewPort());
    }

    p_->draw();
}

}  // namespace haf::scene

#include <haf/include/scene_components/camera_component.hpp>
#include <backend_dev/include/icamera.hpp>
#include "render/render_system.hpp"
#include "render/render_target.hpp"
#include "system/get_system.hpp"

using namespace haf::types;

namespace haf::scene
{
struct CameraComponent::CameraSceneNodePrivate
{
    htps::rptr<backend::ICamera> icamera_{nullptr};
};

void CameraComponent::onAttached()
{
    view     = decltype(view)::value_type{{0, 0}, {1000, 1000}};
    viewPort = decltype(viewPort)::value_type{{0, 0}, {1, 1}};
}

void CameraComponent::update()
{
    bool const is_dirty{view.hasChanged() || viewPort.hasChanged()};

    if (view.readResetHasChanged())
    {
        p_->icamera_->setFarRect(view());
    }

    if (viewPort.readResetHasChanged())
    {
        p_->icamera_->setViewPort(viewPort());
    }

    if (is_dirty)
    {
        sys::getSystem<sys::RenderSystem>(attachedNode())
            .currentRenderTarget()
            ->draw(p_->icamera_);
    }
}

}  // namespace haf::scene

#include <haf/include/scene_components/camera_component.hpp>
#include <backend_dev/include/camera_data.hpp>
#include "render/render_system.hpp"
#include "render/render_target.hpp"
#include "system/get_system.hpp"
#include "scene_components_log.hpp"

using namespace htps;

namespace haf::scene
{
struct CameraComponent::CameraComponentPrivate
{
    backend::CameraData m_camera_data{};
    sptr<sys::RenderTarget> render_target_{};

    void draw() { render_target_->draw(m_camera_data); }
};

CameraComponent::CameraComponent() : p_{make_pimplp<CameraComponentPrivate>()}
{}

CameraComponent::~CameraComponent() = default;

void CameraComponent::onAttached()
{
    p_->render_target_ =
        sys::getSystem<sys::RenderSystem>(attachedNode()).currentRenderTarget();

    view     = decltype(view)::value_type{{-0.5F, -0.5F}, {1.0F, 1.0F}};
    viewPort = decltype(viewPort)::value_type{{0, 0}, {1, 1}};
}

void CameraComponent::moveView(SceneCoordinates const& delta)
{
    view = view() + delta;
}

void CameraComponent::update()
{
    p_->m_camera_data.update_required = false;

    if (view.readResetHasChanged())
    {
        p_->m_camera_data.nearRect        = view();
        p_->m_camera_data.update_required = true;
    }

    if (viewPort.readResetHasChanged())
    {
        p_->m_camera_data.viewPort        = viewPort();
        p_->m_camera_data.update_required = true;
    }

    SceneComponentsLogDisplayer::debug_if(p_->m_camera_data.update_required,
                                          "Updating camera view...");
    SceneComponentsLogDisplayer::debug_if(p_->m_camera_data.update_required,
                                          "view: ", view(),
                                          " ViewPort: ", viewPort());

    p_->draw();
}

}  // namespace haf::scene

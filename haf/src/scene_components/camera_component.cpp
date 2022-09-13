#include <haf/include/scene_components/camera_component.hpp>
#include <haf/include/scene/matrix4x4.hpp>
#include <haf/include/scene/transformation.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/properties/property_state.hpp>
#include "render/render_system.hpp"
#include "render/render_target.hpp"
#include "system/get_system.hpp"
#include "scene_components_log.hpp"

using namespace htps;

namespace haf::scene
{
struct CameraComponent::CameraComponentPrivate
{
    sptr<sys::RenderTarget> render_target_{};
    scene::Transformation transformation;

    // Temporary constants for window size
    vector2df vp_size{800.0F, 600.0F};

    void updateViewport(Rectf32 const& viewPort) noexcept
    {
        render_target_->ViewPort = {
            static_cast<s32>(0.5F + (vp_size.x * viewPort.left)),
            static_cast<s32>(0.5F + (vp_size.y * viewPort.top)),
            static_cast<s32>(0.5F + (vp_size.x * viewPort.width)),
            static_cast<s32>(0.5F + (vp_size.y * viewPort.height))};
    }

    void updateTransform(Rectf32 const& view, f32 const, f32 const) noexcept
    {
        transformation.Position = view.center();
        transformation.Scale    = vector2df{2.0F, -2.0F} / view.size();
        transformation.updateTransformIfNecessary();
        render_target_->Projection = transformation.matrix();
    }
};

CameraComponent::CameraComponent() : p_{make_pimplp<CameraComponentPrivate>()}
{}

CameraComponent::~CameraComponent() = default;

void CameraComponent::onAttached()
{
    p_->render_target_ =
        sys::getSystem<sys::RenderSystem>(attachedNode()).currentRenderTarget();

    view     = decltype(view)::value_type{vector2df{-0.5F, -0.5F},
                                      vector2df{1.0F, 1.0F}};
    Near     = 0.0F;
    Far      = 1.0F;
    viewPort = decltype(viewPort)::value_type{{0, 0}, {1, 1}};
}

void CameraComponent::moveView(SceneCoordinates const& delta)
{
    view = view() + delta;
}

void CameraComponent::update()
{
    if (ps_readResetHasAnyChanged(view, Near, Far))
    {
        SceneComponentsLogDisplayer::debug("Updating camera view...\n",
                                           "view: ", view(),
                                           " ViewPort: ", viewPort());
        p_->updateTransform(view(), Near(), Far());
    }

    if (viewPort.readResetHasChanged())
    {
        SceneComponentsLogDisplayer::debug("Updating camera viewport...\n",
                                           "view: ", view(),
                                           " ViewPort: ", viewPort());
        p_->updateViewport(viewPort());
    }
}

}  // namespace haf::scene

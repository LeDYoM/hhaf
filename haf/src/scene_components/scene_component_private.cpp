#include "scene_component_private.hpp"
#include "../scene/scene_controller.hpp"

#include <haf/include/system/isystem_provider.hpp>
#include <haf/include/system/system_access.hpp>
#include <haf/include/system/subsystem_view.hpp>

using namespace htps;

namespace haf::scene
{
SceneComponent::SceneComponentPrivate::SceneComponentPrivate(
    htps::rptr<SceneComponent> _this) noexcept :
    scene_{_this}
{}

SceneComponent::SceneComponentPrivate::~SceneComponentPrivate() = default;

void SceneComponent::SceneComponentPrivate::setSystemProvider(
    htps::rptr<sys::ISystemProvider> isystem_provider) noexcept
{
    isystem_provider_ = isystem_provider;
    auto sceneNode{scene_->attachedNode()};
    static_cast<sys::SubSystemViewer*>(sceneNode)->isystem_provider_ =
        isystem_provider;
    static_cast<sys::SystemAccess*>(sceneNode)->isystem_provider_ =
        isystem_provider;
}

htps::rptr<sys::ISystemProvider>
SceneComponent::SceneComponentPrivate::iSystemProvider() const noexcept
{
    return isystem_provider_;
}

}  // namespace haf::scene

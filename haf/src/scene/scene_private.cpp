#include "scene_private.hpp"
#include "scene_controller.hpp"

#include <haf/include/system/isystem_provider.hpp>
#include <haf/include/system/system_access.hpp>
#include <haf/include/system/subsystem_view.hpp>
#include <haf/include/scene/scene.hpp>

using namespace htps;

namespace haf::scene
{
Scene::ScenePrivate::ScenePrivate(htps::rptr<Scene> _this) noexcept :
    scene_{_this}
{}

void Scene::ScenePrivate::setSystemProvider(
    htps::rptr<sys::ISystemProvider> isystem_provider) noexcept
{
    isystem_provider_ = isystem_provider;
    static_cast<sys::SubSystemViewer*>(scene_)->isystem_provider_ =
        isystem_provider;
    static_cast<sys::SystemAccess*>(scene_)->isystem_provider_ =
        isystem_provider;
}

}  // namespace haf::scene

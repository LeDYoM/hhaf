#include "scenemanager_accessor.hpp"

#include "scenenode.hpp"
#include "scenemanager.hpp"

namespace lib::scene
{
SceneManagerAccessor::SceneManagerAccessor(rptr<SceneManager> scene_manager)
    : scene_manager_{std::move(scene_manager)} {}

const SceneManager &SceneManagerAccessor::sceneManager() const noexcept
{
    return *scene_manager_;
}

SceneManager &SceneManagerAccessor::sceneManager() noexcept
{
    return *scene_manager_;
}

} // namespace lib::scene

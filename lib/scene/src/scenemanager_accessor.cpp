#include "scenemanager_accessor.hpp"

#include "scenenode.hpp"
#include "scenemanager.hpp"

#include <lib/system/include/isystemprovider.hpp>
#include <lib/system/i_include/systemprovider.hpp>

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

const sys::ISystemProvider& SceneManagerAccessor::isystemProvider() const noexcept
{
    return sceneManager().isystemProvider();
}

sys::ISystemProvider& SceneManagerAccessor::isystemProvider() noexcept
{
    return sceneManager().isystemProvider();
}

} // namespace lib::scene

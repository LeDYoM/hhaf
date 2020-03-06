#include "systemaccess.hpp"

#include "scenenode.hpp"
#include "scenemanager.hpp"

#include <lib/system/include/isystemprovider.hpp>
#include <lib/system/i_include/systemprovider.hpp>

namespace lib::scene
{
SystemAccess::SystemAccess(rptr<SceneManager> scene_manager)
    : scene_manager_{std::move(scene_manager)} {}

const SceneManager &SystemAccess::sceneManager() const noexcept
{
    return *scene_manager_;
}

SceneManager &SystemAccess::sceneManager() noexcept
{
    return *scene_manager_;
}

const sys::ISystemProvider& SystemAccess::isystemProvider() const noexcept
{
    return sceneManager().isystemProvider();
}

sys::ISystemProvider& SystemAccess::isystemProvider() noexcept
{
    return sceneManager().isystemProvider();
}

} // namespace lib::scene

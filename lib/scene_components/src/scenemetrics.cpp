#include "scenemetrics.hpp"
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager.hpp>
#include <lib/system/i_include/get_system.hpp>

namespace lib::scene
{
Rectf32 SceneMetrics::currentView() noexcept
{
    return sys::getSystem<SceneManager>(attachedNode()).viewRect();
}

} // namespace lib::scene

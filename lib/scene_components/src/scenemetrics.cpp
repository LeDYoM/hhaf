#include "scenemetrics.hpp"
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/i_include/scenemanager.hpp>
#include <lib/system/i_include/get_system.hpp>

namespace lib::scene
{
Rectf32 SceneMetrics::currentView() const
{
    return sys::getSystem<SceneManager>(attachedNode()).viewRect();
}

} // namespace lib::scene

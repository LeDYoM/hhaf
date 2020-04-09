#include "scenemetrics.hpp"
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/i_include/scenemanager.hpp>
#include <haf/system/i_include/get_system.hpp>

using namespace mtps;

namespace haf::scene
{
Rectf32 SceneMetrics::currentView() const
{
    return sys::getSystem<SceneManager>(attachedNode()).viewRect();
}

} // namespace haf::scene

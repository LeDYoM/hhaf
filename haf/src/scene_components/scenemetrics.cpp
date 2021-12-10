#include <haf/include/scene_components/scenemetrics.hpp>
#include "scene/scene_manager.hpp"
#include "system/get_system.hpp"

#include <hlog/include/hlog.hpp>

namespace haf::scene
{
void SceneMetrics::setViewRect(SceneBox const& new_view)
{
    getSystem<SceneManager>(attachedNode()).setViewRect(new_view);
}

void SceneMetrics::setViewPort(SceneBox const& new_view_port)
{
    getSystem<SceneManager>(attachedNode()).setViewPort(new_view_port);
}

void SceneMetrics::move(SceneCoordinates const& delta)
{
    DisplayLog::debug("Current view: ", BaseClass::currentView());
    setViewRect(BaseClass::currentView() + delta);
    DisplayLog::debug("Current view after set: ", currentView());
}

}  // namespace haf::scene

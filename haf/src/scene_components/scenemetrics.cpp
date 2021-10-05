#include <haf/include/scene_components/scenemetrics.hpp>
#include "scene/scenemanager.hpp"
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
    auto current = BaseClass::currentView();
    DisplayLog::debug("Current view: ", current);
    current += delta;
    DisplayLog::debug("Going to set view: ", current);
    setViewRect(current);
    DisplayLog::debug("Current view after set: ", currentView());
}

}  // namespace haf::scene
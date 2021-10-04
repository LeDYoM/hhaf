#include <haf/include/scene_components/scenemetrics.hpp>
#include "scene/scenemanager.hpp"
#include "system/get_system.hpp"

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
    current += delta;
    setViewRect(current);
}

}  // namespace haf::scene
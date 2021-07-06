#include <haf/include/scene_components/scenemetrics.hpp>
#include "scene/scenemanager.hpp"
#include "system/get_system.hpp"

using namespace htps;

namespace haf::scene
{
void SceneMetrics::setViewRect(Rectf32 const& new_view)
{
    getSystem<SceneManager>(attachedNode()).setViewRect(new_view);
}

void SceneMetrics::setViewPort(Rectf32 const& new_view_port)
{
    getSystem<SceneManager>(attachedNode()).setViewPort(new_view_port);
}

}  // namespace haf::scene
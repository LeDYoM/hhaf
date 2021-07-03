#include <haf/include/scene_components/scenemetrics.hpp>
#include "scene/scenemanager.hpp"
#include "system/get_system.hpp"

namespace haf::scene
{
void SceneMetrics::setViewRect(const htps::Rectf32& new_view)
{
    getSystem<scene::SceneManager>(attachedNode()).setViewRect(new_view);
}

void SceneMetrics::setViewPort(const htps::Rectf32& new_view_port)
{
    getSystem<scene::SceneManager>(attachedNode()).setViewPort(new_view_port);
}

}  // namespace haf::scene
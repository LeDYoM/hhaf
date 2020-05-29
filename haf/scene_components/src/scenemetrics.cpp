#include "scenemetrics.hpp"
#include <haf/scene/include/scenenode.hpp>
#include <scene/i_include/scenemanager.hpp>
#include <system/i_include/get_system.hpp>

using namespace mtps;

namespace haf::scene
{
void SceneMetrics::setViewRect(const mtps::Rectf32& new_view)
{
    sys::getSystem<SceneManager>(attachedNode()).setViewRect(new_view);
}

void SceneMetrics::setViewPort(const mtps::Rectf32& new_view_port)
{
    sys::getSystem<SceneManager>(attachedNode()).setViewPort(new_view_port);
}

}  // namespace haf::scene

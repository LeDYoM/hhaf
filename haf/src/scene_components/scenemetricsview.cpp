#include <haf/include/scene_components/scenemetricsview.hpp>
#include "scene/scenemanager.hpp"

#include "system/get_system.hpp"

namespace haf::scene
{
SceneBox SceneMetricsView::currentView() const
{
    return sys::getSystem<scene::SceneManager>(attachedNode()).currentView();
}

SceneBox SceneMetricsView::currentViewPort() const
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .currentViewPort();
}

}  // namespace haf::scene
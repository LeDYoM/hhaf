#include <haf/include/scene_components/scenemetricsview.hpp>
#include "scene/scenemanager.hpp"

#include "system/get_system.hpp"

using namespace htps;

namespace haf::scene
{
Rectf32 SceneMetricsView::currentView() const
{
    return sys::getSystem<scene::SceneManager>(attachedNode()).currentView();
}

Rectf32 SceneMetricsView::currentViewPort() const
{
    return sys::getSystem<scene::SceneManager>(attachedNode())
        .currentViewPort();
}

}  // namespace haf::scene
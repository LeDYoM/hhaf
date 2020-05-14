#include "scenemetricsview.hpp"
#include <haf/scene/include/scenenode.hpp>
#include <scene/i_include/scenemanager.hpp>
#include <system/i_include/get_system.hpp>

using namespace mtps;

namespace haf::scene
{
Rectf32 SceneMetricsView::currentView() const
{
    return sys::getSystem<SceneManager>(attachedNode()).viewRect();
}

Rectf32 SceneMetricsView::currentViewPort() const
{
    return sys::getSystem<SceneManager>(attachedNode()).viewPort();
}

} // namespace haf::scene

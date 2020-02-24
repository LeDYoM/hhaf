#include "scenemetrics.hpp"
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager.hpp>

namespace lib::scene
{
Rectf32 SceneMetrics::currentView() noexcept
{
    return attachedNode()->sceneManager().viewRect();
}

} // namespace lib::scene

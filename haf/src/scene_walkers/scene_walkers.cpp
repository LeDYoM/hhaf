#include <haf/include/scene_walkers/scene_walkers.hpp>

namespace haf::walk
{
void SceneWalkers::addPrivateSceneWalkers()
{
    m_orders.push_back(0);
    m_orders.push_back(1);
}

void SceneWalkers::sceneWalk()
{}
}  // namespace haf::walk

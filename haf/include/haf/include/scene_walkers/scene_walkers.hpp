HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_WALKERS_SCENE_WALKERS_INCLUDE_HPP
#define HAF_SCENE_WALKERS_SCENE_WALKERS_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component_order.hpp>

namespace haf::walk
{
class SceneWalkers
{
public:
    void addPrivateSceneWalkers();
    void sceneWalk();

private:
    core::vector<component::ComponentOrder::Value> m_orders;
};
}  // namespace haf::walk
#endif

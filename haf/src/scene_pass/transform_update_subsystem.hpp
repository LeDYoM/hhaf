HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TRANSFORM_UPDATE_SUBSYSTEM_INCLUDE_HPP
#define HAF_SCENE_TRANSFORM_UPDATE_SUBSYSTEM_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/component/component.hpp>
#include "scene_subsystem.hpp"

namespace haf::scene
{
class TransformScene
{
public:
    void init();
    void finish();
    void initPass();
    void finishPass();
    void update();
    void updateNodeDownTree(SceneNode& node, htps::sptr<component::Component> );
};

}  // namespace haf::scene

#endif

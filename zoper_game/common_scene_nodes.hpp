#ifndef ZOPER_COMMON_SCENE_NODES_INCLUDE_HPP
#define ZOPER_COMMON_SCENE_NODES_INCLUDE_HPP

#include <haf/include/scene_nodes/renderizable_scene_node.hpp>

namespace zoper
{
void createStandardBackground(
    htps::sptr<haf::scene::RenderizableSceneNode> const&
        renderizable_scene_node);
}  // namespace zoper

#endif

#ifndef ZOPER_COMMON_SCENE_NODES_INCLUDE_HPP
#define ZOPER_COMMON_SCENE_NODES_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>

namespace zoper
{
void createStandardBackground(
    haf::render::RenderizableBuilder&& renderizable_builder);

void createStandardBackground(
    haf::types::sptr<haf::scene::RenderizableSceneNode> const& renderizable_scene_node);
}  // namespace zoper

#endif

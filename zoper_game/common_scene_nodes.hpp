#ifndef ZOPER_COMMON_SCENE_NODES_INCLUDE_HPP
#define ZOPER_COMMON_SCENE_NODES_INCLUDE_HPP

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/render/renderizable_builder.hpp>

namespace zoper
{
void createStandardBackground(
    haf::render::RenderizableBuilder&& renderizable_builder);
}

#endif

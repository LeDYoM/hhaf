#include "common_scene_nodes.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/render/renderizables.hpp>

using namespace htps;
using namespace haf::scene;
using namespace haf::render;

namespace zoper
{
void createStandardBackground(
    sptr<RenderizableSceneNode> const& renderizable_scene_node)
{
    renderizable_scene_node->renderizableBuilder()
        .name("background")
        .figType(FigType_t::Sprite)
        .create();
}

}  // namespace zoper

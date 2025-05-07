#include "common_scene_nodes.hpp"
#include <haf/include/core/types.hpp>
#include <haf/include/properties/iproperty.hpp>
#include <haf/include/scene_components/renderizables.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/scene_node.hpp>

using namespace htps;
using namespace haf::scene;
using namespace haf::render;

namespace zoper
{
void createStandardBackground(SceneNodeSPtr const& scene_node)
{
    auto renderizable_scene_node{
        scene_node->component<RenderizableGroupComponent>()};
    renderizable_scene_node->renderizableBuilder()
        .name("background")
        .figType(FigType_t::Sprite)
        .create();
}

}  // namespace zoper

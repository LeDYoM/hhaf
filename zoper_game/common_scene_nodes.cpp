#include "common_scene_nodes.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_modifier_context.hpp>

using namespace haf;
using namespace haf::types;
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
        .colorModifier([](const RenderizableModifierContext& context) {
            const auto n = context.normalizedVertexInBox();
            static constexpr auto decrease_ratio = 0.4F;
            return Color::fromFloats(n.y * decrease_ratio, n.y * decrease_ratio,
                                     n.y * decrease_ratio);
        })
        .create();
}

}  // namespace zoper

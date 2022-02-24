#include "common_scene_nodes.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_modifier_context.hpp>

using namespace htps;
using namespace haf;
using namespace haf::types;
using namespace haf::scene;
using namespace haf::render;

namespace zoper
{
void createStandardBackground(RenderizableBuilder&& renderizable_builder)
{
    auto background{
        renderizable_builder.name("background")
            .figType(FigType_t::Quad)
            .box(rectFromSize(2000.0f, 2000.0f))
            .colorModifier([](const RenderizableModifierContext& context) {
                const auto n = context.normalizedVertexInBox();
                static constexpr auto decrease_ratio = 0.5F;
                return Color::fromFloats(n.y * decrease_ratio,
                                         n.y * decrease_ratio,
                                         n.y * decrease_ratio);
            })
            .create()};
}

void createStandardBackground(
    haf::types::sptr<haf::scene::RenderizableSceneNode> const&
        renderizable_scene_node)
{
    renderizable_scene_node->prop<Position>().set(vector2df{1000.0F, 0.0F});
    renderizable_scene_node->prop<Scale>().set(vector2df{500.0F, 500.0F});
    auto background{
        renderizable_scene_node->renderizableBuilder()
            .name("background")
            .figType(FigType_t::Sprite)
//            .box(rectFromSize(2000.0f, 2000.0f))
            .colorModifier([](const RenderizableModifierContext& context) {
                const auto n = context.normalizedVertexInBox();
                static constexpr auto decrease_ratio = 0.4F;
                return Color::fromFloats(n.y * decrease_ratio,
                                         n.y * decrease_ratio,
                                         n.y * decrease_ratio);
            })
            .create()};
}

}  // namespace zoper

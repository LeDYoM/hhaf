#include <htypes/include/types.hpp>
#include <htypes/include/properties.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_modifier_context.hpp>

namespace zoper
{
using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::render;

void createStandardBackground(RenderizableBuilder& renderizable_builder)
{
    auto background =
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
            .create();

    background->color_modifier =
        [](const RenderizableModifierContext& context) {
            const auto n = context.normalizedVertexInBox();
            static constexpr auto decrease_ratio = 0.5F;
            return Color::fromFloats(n.y * decrease_ratio, n.y * decrease_ratio,
                                     n.y * decrease_ratio);
        };
}
}  // namespace zoper

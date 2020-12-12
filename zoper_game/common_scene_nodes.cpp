#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/render/include/renderizable.hpp>
#include <haf/scene/include/scenenode.hpp>

namespace zoper
{
using namespace mtps;
using namespace haf;
using namespace haf::scene;

void createStandardBackground(
    const rptr<haf::scene::Renderizables> renderizables)
{
    auto background =
        renderizables->renderizableBuilder()
            .name("background")
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

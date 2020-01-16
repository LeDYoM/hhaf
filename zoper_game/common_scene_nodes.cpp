#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>

#include <lib/include/liblog.hpp>
#include <lib/scene/renderizables/renderizable.hpp>
#include <lib/scene/components/renderizables.hpp>
#include <lib/scene/scenenode.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;

void createStandardBackground(
    const sptr<lib::scene::Renderizables> &renderizables)
{
    auto background = renderizables->createRenderizable(
        "background", FigType_t::Quad, rectFromSize(2000.0f, 2000.0f));
    background->color_modifier = [](const RenderizableModifierContext &context) {
        const auto n = context.normalizedVertexInBox();
        static constexpr auto decrease_ratio = 0.5F;
        return Color::fromFloats(
            n.y * decrease_ratio, n.y * decrease_ratio, n.y * decrease_ratio);
    };

    //        background->shader = resources_viewer->getShader(MainMenuResources::Shader);
}
} // namespace zoper

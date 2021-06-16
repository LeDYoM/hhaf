#ifndef HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/function.hpp>

#include <haf/include/scene/color.hpp>

namespace haf::res
{
class IShader;
class ITexture;
}  // namespace haf::res

namespace haf::render
{
struct RenderizableModifierContext;
enum class FigType_t : htps::u8;
class Renderizables;
}  // namespace haf::render

namespace haf::render
{
struct RenderizableBuilderData
{
    htps::rptr<Renderizables> renderizables_;
    htps::str name_;
    FigType_t figType_;
    htps::Rectf32 box_{};
    scene::Color color_{scene::colors::White};
    htps::size_type pointCount_{4U};
    htps::sptr<res::IShader> shader_{nullptr};
    htps::sptr<res::ITexture> texture_{nullptr};
    htps::function<scene::Color(const RenderizableModifierContext&)>
        color_modifier_{};
};
}  // namespace haf::render

#endif

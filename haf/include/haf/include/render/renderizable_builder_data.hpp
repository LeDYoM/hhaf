#ifndef HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP
#define HAF_RENDERIZABLE_BUILDER_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/function.hpp>

#include <haf/include/scene/color.hpp>

namespace haf::scene
{
class Renderizables;
class Renderizable;
struct RenderizableModifierContext;
enum class FigType_t : htps::u8;
}  // namespace haf::scene

namespace haf::res
{
class IShader;
class ITexture;
}  // namespace haf::res

namespace haf::render
{
struct RenderizableBuilderData
{
    htps::rptr<scene::Renderizables> renderizables_;
    htps::str name_;
    scene::FigType_t figType_;
    htps::Rectf32 box_{};
    scene::Color color_{scene::colors::White};
    htps::size_type pointCount_{4U};
    htps::sptr<res::IShader> shader_{nullptr};
    htps::sptr<res::ITexture> texture_{nullptr};
    htps::function<scene::Color(const scene::RenderizableModifierContext&)>
        color_modifier_{};
};
}  // namespace haf::scene

#endif

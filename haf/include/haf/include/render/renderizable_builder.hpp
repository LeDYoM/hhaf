#ifndef HAF_RENDERIZABLE_BUILDER_INCLUDE_HPP
#define HAF_RENDERIZABLE_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/function.hpp>

#include <haf/include/scene/color.hpp>
#include <haf/include/render/renderizable_modifier_context.hpp>

namespace haf::scene
{
class Renderizables;
class Renderizable;
enum class FigType_t : htps::u8;
}  // namespace haf::scene

namespace haf::res
{
class IShader;
class ITexture;
}  // namespace haf::res

namespace haf::scene
{
class RenderizableBuilder
{
public:
    RenderizableBuilder(htps::rptr<Renderizables> renderizables) noexcept;

    htps::sptr<Renderizable> create();

    RenderizableBuilder& name(htps::str _name);
    RenderizableBuilder& figType(FigType_t fig_type);
    RenderizableBuilder& box(htps::Rectf32 _box);
    RenderizableBuilder& color(Color _color);
    RenderizableBuilder& pointCount(htps::size_type point_count);
    RenderizableBuilder& shader(htps::sptr<res::IShader> _shader);
    RenderizableBuilder& texture(htps::sptr<res::ITexture> _texture);
    RenderizableBuilder& colorModifier(
        htps::function<Color(const RenderizableModifierContext&)>
            color_modifier);

    struct Data
    {
        htps::rptr<Renderizables> renderizables_;
        htps::str name_;
        FigType_t figType_;
        htps::Rectf32 box_{};
        Color color_{colors::White};
        htps::size_type pointCount_{4U};
        htps::sptr<res::IShader> shader_{nullptr};
        htps::sptr<res::ITexture> texture_{nullptr};
        htps::function<Color(const RenderizableModifierContext&)>
            color_modifier_{};
    };

    const Data& data() const { return data_; }

private:
    RenderizableBuilder::Data data_;
};
}  // namespace haf::scene

#endif

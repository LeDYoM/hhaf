#ifndef HAF_RENDERIZABLE_BUILDER_INCLUDE_HPP
#define HAF_RENDERIZABLE_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/function.hpp>

#include <haf/include/scene/color.hpp>
#include <haf/include/render/renderizable_builder_data.hpp>

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
/**
 * @brief Class to help the building of @b Renderizable objects
 * This class implements the builder pattern to facilitate the
 * building of new renderizable objects
 */
class RenderizableBuilder
{
public:
    
    explicit RenderizableBuilder(
        htps::rptr<scene::Renderizables> renderizables) noexcept;

    htps::sptr<scene::Renderizable> create();

    RenderizableBuilder& name(htps::str _name);
    RenderizableBuilder& figType(scene::FigType_t fig_type);
    RenderizableBuilder& box(htps::Rectf32 _box);
    RenderizableBuilder& color(scene::Color _color);
    RenderizableBuilder& pointCount(htps::size_type point_count);
    RenderizableBuilder& shader(htps::sptr<res::IShader> _shader);
    RenderizableBuilder& texture(htps::sptr<res::ITexture> _texture);
    RenderizableBuilder& colorModifier(
        htps::function<scene::Color(const scene::RenderizableModifierContext&)>
            color_modifier);

private:
    RenderizableBuilderData data_;
};
}  // namespace haf::scene

#endif

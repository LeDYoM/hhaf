HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLE_BUILDER_INCLUDE_HPP
#define HAF_RENDERIZABLE_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/rect.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/function.hpp>

#include <haf/include/scene/color.hpp>
#include <haf/include/render/renderizable_builder_data.hpp>

namespace haf::res
{
class IShader;
class ITexture;
}  // namespace haf::res

namespace haf::render
{
class Renderizable;
class Renderizables;
enum class FigType_t : htps::u8;
}  // namespace haf::render

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
        htps::rptr<Renderizables> renderizables) noexcept;

    htps::sptr<Renderizable> create();

    RenderizableBuilder& name(htps::str const& _name);
    RenderizableBuilder& figType(FigType_t const& fig_type);
    RenderizableBuilder& color(scene::Color const& _color);
    RenderizableBuilder& pointCount(htps::size_type const& point_count);
    RenderizableBuilder& shader(htps::sptr<res::IShader> _shader);
    RenderizableBuilder& shader(htps::str const& shader_name);
    RenderizableBuilder& texture(htps::sptr<res::ITexture> _texture);
    RenderizableBuilder& texture(htps::str const& texture_name);
private:
    RenderizableBuilderData data_;
};
}  // namespace haf::render

#endif

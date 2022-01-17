#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/render/renderizables.hpp>

#include <utility>

namespace haf::render
{

RenderizableBuilder::RenderizableBuilder(
    htps::rptr<Renderizables> renderizables) noexcept :
    data_{RenderizableBuilderData{std::move(renderizables), {}}}
{
    data_.builder_data_.prop<FigureTypeProperty>() = FigType_t::Shape;
    data_.builder_data_.prop<ColorProperty>()      = scene::colors::White;
    data_.builder_data_.prop<PointCount>()         = 4U;
}

htps::sptr<Renderizable> RenderizableBuilder::create()
{
    return data_.renderizables_->createRenderizable(std::move(data_));
}

RenderizableBuilder& RenderizableBuilder::name(types::str const& _name)
{
    data_.builder_data_.prop<RenderizableName>() = _name;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::figType(FigType_t const& fig_type)
{
    data_.builder_data_.prop<FigureTypeProperty>() = fig_type;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::box(SceneBox const& _box)
{
    data_.builder_data_.prop<BoxProperty>() = _box;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::color(scene::Color const& _color)
{
    data_.builder_data_.prop<ColorProperty>() = _color;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::pointCount(
    htps::size_type const& point_count)
{
    data_.builder_data_.prop<PointCount>() = point_count;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(
    htps::sptr<res::IShader> _shader)
{
    data_.builder_data_.prop<ShaderProperty>() = std::move(_shader);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::texture(
    htps::sptr<res::ITexture> _texture)
{
    data_.builder_data_.prop<TextureProperty>() = std::move(_texture);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::colorModifier(
    htps::function<scene::Color(const RenderizableModifierContext&)>
        color_modifier)
{
    data_.builder_data_.prop<ColorModifierProperty>() =
        std::move(color_modifier);
    return *this;
}

RenderizableBuilder&& RenderizableBuilder::get() noexcept
{
    return std::move(*this);
}

RenderizableBuilderData&& RenderizableBuilder::extract() noexcept
{
    return std::move(data_);
}

}  // namespace haf::render

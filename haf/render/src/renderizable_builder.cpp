#include <haf/render/include/renderizable_builder.hpp>
#include <haf/render/include/renderizables.hpp>

namespace haf::scene
{

RenderizableBuilder::RenderizableBuilder(
    htps::rptr<Renderizables> renderizables) noexcept :
    data_{std::move(renderizables)}
{}

htps::sptr<Renderizable> RenderizableBuilder::create()
{
    return data_.renderizables_->createRenderizable(
        data_.name_, data_.figType_, data_.box_, data_.color_, data_.texture_,
        data_.shader_, data_.pointCount_);
}

RenderizableBuilder& RenderizableBuilder::name(htps::str _name)
{
    data_.name_ = std::move(_name);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::figType(FigType_t fig_type)
{
    data_.figType_ = std::move(fig_type);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::box(htps::Rectf32 _box)
{
    data_.box_ = _box;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::color(Color _color)
{
    data_.color_ = std::move(_color);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::pointCount(
    htps::size_type point_count)
{
    data_.pointCount_ = std::move(point_count);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(
    htps::sptr<res::IShader> _shader)
{
    data_.shader_ = std::move(_shader);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::texture(
    htps::sptr<res::ITexture> _texture)
{
    data_.texture_ = std::move(_texture);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::colorModifier(
    htps::function<Color(const RenderizableModifierContext&)> color_modifier)
{
    data_.color_modifier_ = std::move(color_modifier);
    return *this;
}

}  // namespace haf::scene

#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/render/renderizables.hpp>

#include <utility>

namespace haf::render
{

RenderizableBuilder::RenderizableBuilder(
    htps::rptr<Renderizables> renderizables) noexcept :
    data_{RenderizableBuilderData{std::move(renderizables), {}}}
{
    data_.bulder_data_.prop<FigureTypeProperty>() = FigType_t::Shape;
}

htps::sptr<Renderizable> RenderizableBuilder::create() const
{
    return data_.renderizables_->createRenderizable(
        data_.name_, data_.bulder_data_.prop<FigureTypeProperty>()(),
        data_.bulder_data_.prop<RenderizableSceneBoxProperty>()(), data_.color_,
        data_.texture_, data_.shader_, data_.pointCount_);
}

RenderizableBuilder& RenderizableBuilder::name(htps::str _name)
{
    data_.name_.swap(_name);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::figType(FigType_t fig_type)
{
    data_.bulder_data_.prop<FigureTypeProperty>() = std::move(fig_type);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::box(htps::Rectf32 _box)
{
    data_.bulder_data_.prop<RenderizableSceneBoxProperty>() = std::move(_box);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::color(scene::Color _color)
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
    htps::function<scene::Color(const RenderizableModifierContext&)>
        color_modifier)
{
    data_.color_modifier_ = std::move(color_modifier);
    return *this;
}

}  // namespace haf::render

#include "renderizable_builder.hpp"
#include "scenenode.hpp"

namespace haf::scene
{

RenderizableBuilder::RenderizableBuilder(
    mtps::str name,
    mtps::rptr<SceneNode> scene_node) noexcept :
    data_{std::move(scene_node), std::move(name)}

{}

mtps::sptr<Renderizable> RenderizableBuilder::create()
{
    return nullptr;
}

RenderizableBuilder& RenderizableBuilder::figType(FigType_t fig_type)
{
    data_.figType_ = std::move(fig_type);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::box(mtps::Rectf32 _box)
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
    mtps::size_type point_count)
{
    data_.pointCount_ = std::move(point_count);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(mtps::sptr<IShader> _shader)
{
    data_.shader_ = std::move(_shader);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::texture(mtps::sptr<ITexture> _texture)
{
    data_.texture_ = std::move(_texture);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::colorModifier(
    mtps::function<Color(const RenderizableModifierContext&)> color_modifier)
{
    data_.color_modifier_ = std::move(color_modifier);
    return *this;
}

}  // namespace haf::scene

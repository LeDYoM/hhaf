#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/scene_nodes/transformable_scene_node.hpp>

namespace haf::render
{

RenderizableBuilder::RenderizableBuilder(
    htps::rptr<Renderizables> renderizables) noexcept :
    data_{RenderizableBuilderData{std::move(renderizables), {}}}
{
    data_.builder_data_.prop<FigureTypeProperty>() = FigType_t::Sprite;
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
    data_.builder_data_.prop<PointCount>() = 6U;
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
    data_.builder_data_.prop<PointCount>() = point_count * 3U;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(
    htps::sptr<res::IShader> _shader)
{
    data_.builder_data_.prop<ShaderProperty>() = std::move(_shader);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(htps::str const& shader_name)
{
    return shader(data_.renderizables_->sceneNode()
                      ->subSystem<res::IResourceRetriever>()
                      ->getShader(shader_name));
}

RenderizableBuilder& RenderizableBuilder::texture(
    htps::sptr<res::ITexture> _texture)
{
    if (_texture != nullptr)
    {
        data_.builder_data_.prop<TextureRectProperty>().set(htps::Rects32{
            0, 0, static_cast<htps::vector2ds32>(_texture->size())});
    }
    data_.builder_data_.prop<TextureProperty>() = std::move(_texture);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::texture(htps::str const& texture_name)
{
    return texture(data_.renderizables_->sceneNode()
                       ->subSystem<res::IResourceRetriever>()
                       ->getTexture(texture_name));
}

}  // namespace haf::render

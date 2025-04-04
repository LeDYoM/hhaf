#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/resources/iresource_retriever.hpp>

using namespace htps;
using namespace fmath;

namespace haf::render
{

RenderizableBuilder::RenderizableBuilder(
    rptr<Renderizables> renderizables) noexcept :
    data_{RenderizableBuilderData{htps::move(renderizables), {}}}
{
    data_.builder_data_.FigureTypeProperty = FigType_t::Sprite;
    data_.builder_data_.ColorProperty      = scene::colors::White;
    data_.builder_data_.PointCount         = 4U;
}

sptr<Renderizable> RenderizableBuilder::create()
{
    return data_.renderizables_->createRenderizable(htps::move(data_));
}

RenderizableBuilder& RenderizableBuilder::name(str const& _name)
{
    data_.builder_data_.RenderizableName = _name;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::figType(FigType_t const& fig_type)
{
    data_.builder_data_.FigureTypeProperty = fig_type;
    data_.builder_data_.PointCount         = 6U;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::color(scene::Color const& _color)
{
    data_.builder_data_.ColorProperty = _color;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::pointCount(
    size_type const& point_count)
{
    data_.builder_data_.PointCount = point_count * 3U;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(sptr<res::IShader> _shader)
{
    data_.builder_data_.ShaderProperty = htps::move(_shader);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(str const& shader_name)
{
    return shader(data_.renderizables_->sceneNode()
                      ->subSystem<res::IResourceRetriever>()
                      ->getShader(shader_name));
}

RenderizableBuilder& RenderizableBuilder::texture(sptr<res::ITexture> _texture)
{
    if (_texture != nullptr)
    {
        data_.builder_data_.TextureRectProperty =
            Rects32{0, 0, static_cast<vector2ds32>(_texture->size())};
    }
    data_.builder_data_.TextureProperty = htps::move(_texture);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::texture(str const& texture_name)
{
    return texture(data_.renderizables_->sceneNode()
                       ->subSystem<res::IResourceRetriever>()
                       ->getTexture(texture_name));
}

}  // namespace haf::render

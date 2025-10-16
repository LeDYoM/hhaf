#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/resources/iresource_retriever.hpp>

using namespace haf::core;
using namespace fmath;

namespace haf::render
{

RenderizableBuilder::RenderizableBuilder(
    rptr<Renderizables> renderizables) noexcept :
    data_{RenderizableBuilderData{core::move(renderizables)}}
{
    data_.renderizableData().FigureTypeProperty = FigType_t::Sprite;
    data_.renderizableData().ColorProperty      = scene::colors::White;
    data_.renderizableData().PointCount         = 4U;
}

sptr<Renderizable> RenderizableBuilder::create()
{
    return data_.renderizables()->createRenderizable(htps::move(data_));
}

RenderizableBuilder& RenderizableBuilder::name(str const& _name)
{
    data_.renderizableData().RenderizableName = _name;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::figType(FigType_t const& fig_type)
{
    data_.renderizableData().FigureTypeProperty = fig_type;
    data_.renderizableData().PointCount         = 6U;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::color(scene::Color const& _color)
{
    data_.renderizableData().ColorProperty = _color;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::pointCount(
    size_type const& point_count)
{
    data_.renderizableData().PointCount = point_count * 3U;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(sptr<res::IShader> _shader)
{
    data_.renderizableData().ShaderProperty = htps::move(_shader);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(str const& shader_name)
{
    return shader(data_.renderizables()
                      ->sceneNode()
                      ->subSystem<res::IResourceRetriever>()
                      ->getShader(shader_name));
}

RenderizableBuilder& RenderizableBuilder::texture(sptr<res::ITexture> _texture)
{
    if (_texture != nullptr)
    {
        data_.renderizableData().TextureRectProperty =
            Rects32{0, 0, static_cast<vector2ds32>(_texture->size())};
    }
    data_.renderizableData().TextureProperty = htps::move(_texture);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::texture(str const& texture_name)
{
    return texture(data_.renderizables()
                       ->sceneNode()
                       ->subSystem<res::IResourceRetriever>()
                       ->getTexture(texture_name));
}

}  // namespace haf::render

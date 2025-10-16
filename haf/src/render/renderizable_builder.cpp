#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/resources/iresource_retriever.hpp>

using namespace haf::core;
using namespace fmath;

namespace haf::render
{

RenderizableBuilder::RenderizableBuilder(
    rptr<Renderizables> renderizables) noexcept :
    m_data{RenderizableBuilderData{core::move(renderizables)}}
{
    m_data.renderizableData().FigureTypeProperty = FigType_t::Sprite;
    m_data.renderizableData().ColorProperty      = scene::colors::White;
    m_data.renderizableData().PointCount         = 4U;
}

sptr<Renderizable> RenderizableBuilder::create()
{
    return m_data.renderizables()->createRenderizable(htps::move(m_data));
}

RenderizableBuilder& RenderizableBuilder::name(str const& _name)
{
    m_data.renderizableData().RenderizableName = _name;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::figType(FigType_t const& fig_type)
{
    m_data.renderizableData().FigureTypeProperty = fig_type;
    m_data.renderizableData().PointCount         = 6U;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::color(scene::Color const& _color)
{
    m_data.renderizableData().ColorProperty = _color;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::pointCount(
    size_type const& point_count)
{
    m_data.renderizableData().PointCount = point_count * 3U;
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(sptr<res::IShader> _shader)
{
    m_data.renderizableData().ShaderProperty = htps::move(_shader);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::shader(str const& shader_name)
{
    return shader(m_data.renderizables()
                      ->sceneNode()
                      ->subSystem<res::IResourceRetriever>()
                      ->getShader(shader_name));
}

RenderizableBuilder& RenderizableBuilder::texture(sptr<res::ITexture> _texture)
{
    if (_texture != nullptr)
    {
        m_data.renderizableData().TextureRectProperty =
            Rects32{0, 0, static_cast<vector2ds32>(_texture->size())};
    }
    m_data.renderizableData().TextureProperty = htps::move(_texture);
    return *this;
}

RenderizableBuilder& RenderizableBuilder::texture(str const& texture_name)
{
    return texture(m_data.renderizables()
                       ->sceneNode()
                       ->subSystem<res::IResourceRetriever>()
                       ->getTexture(texture_name));
}

}  // namespace haf::render

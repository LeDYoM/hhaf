#include <haf/render/include/renderizable.hpp>
#include <render/i_include/rendersystem.hpp>

#include <haf/render/include/renderdata.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/render/include/renderizable_builder.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ishader.hpp>
#include <system/i_include/get_system.hpp>

#include <haf/render/include/geometry_math.hpp>

using namespace htps;

namespace haf::scene
{
namespace
{
constexpr vector2dd getPositionFromAngleAndRadius(const FigType_t fig_type,
                                                  const f64 angle,
                                                  const vector2df& radius)
{
    switch (fig_type)
    {
        default:
        case FigType_t::Quad:
        {
            return {(sgn_cos(angle) * radius.x), sgn_sin(angle) * radius.y};
        }
        break;
        case FigType_t::Shape:
        {
            return {std::cos(angle) * radius.x, std::sin(angle) * radius.y};
        }
    }
}

constexpr pair<PrimitiveType, size_type> initDataVertexPerFigureAndNumPoints(
    const FigType_t fig_type,
    const size_type num_points) noexcept
{
    switch (fig_type)
    {
        default:
        case FigType_t::Quad:
        case FigType_t::Shape:
        {
            return {PrimitiveType::TriangleFan, num_points + 2U};
        }
        break;
        case FigType_t::EmptyQuad:
        {
            return {PrimitiveType::LineStrip, num_points + 1U};
        }
        break;
    }
}

Rects32 textureFillQuad(const sptr<res::ITexture>& texture)
{
    return texture ? Rects32{0, 0, static_cast<vector2ds32>(texture->size())}
                   : Rects32{};
}

vector2df normalizeInBox(const vector2df& position,
                         Renderizable::RenderizableInternalData const& data)
{
    const f32 xratio{(position.x - data.box.left) / data.box.width};
    const f32 yratio{(position.y - data.box.top) / data.box.height};
    return {(data.textureRect.left + (data.textureRect.width * xratio)),
            (data.textureRect.top + (data.textureRect.height * yratio))};
}

void updateColorForVertex(Renderizable::RenderizableInternalData const& data,
                          BasicVertexArray::value_type& vertex)
{
    Color dest_color{data.color};
    if (data.color_modifier)
    {
        RenderizableModifierContext context{
            data.box, data.textureRect,
            data.texture ? data.texture->size() : vector2du32{0U, 0U}, vertex};
        dest_color *= data.color_modifier(context);
    }
    vertex.color = dest_color;
}

void updateColors(BasicVertexArray& vertices,
                  Renderizable::RenderizableInternalData const& data)
{
    for (auto& vertex : vertices)
    {
        updateColorForVertex(data, vertex);
    }
}

void updateTextureCoordsAndColorForVertex(
    const BasicVertexArray::iterator v_iterator,
    Renderizable::RenderizableInternalData const& iData)
{
    auto& dest_vertex     = *v_iterator;
    dest_vertex.texCoords = normalizeInBox(dest_vertex.position, iData);
    updateColorForVertex(iData, dest_vertex);
}

void updateTextureCoordsAndColor(
    BasicVertexArray& vertices,
    Renderizable::RenderizableInternalData const& data)
{
    for (auto& vertex : vertices)
    {
        updateTextureCoordsAndColorForVertex(&vertex, data);
    }
}

}  // namespace

struct Renderizable::RenderizablePrivate
{};

Renderizable::Renderizable(rptr<SceneNode> parent,
                           str name,
                           FigType_t figure_type,
                           size_type initial_point_count,
                           Rectf32 _box,
                           Color _color,
                           sptr<res::ITexture> _texture,
                           sptr<res::IShader> _shader) :
    sys::HasName{std::move(name)},
    SceneNodeParent{parent},
    p_{make_pimplp<RenderizablePrivate>()},
    figType{figure_type},
    pointCount{initial_point_count},
    box{std::move(_box)},
    color{std::move(_color)},
    shader{std::move(_shader)},
    textureRect{textureFillQuad(_texture)},
    texture{std::move(_texture)},
    m_vertices{
        initDataVertexPerFigureAndNumPoints(figure_type, initial_point_count)},
    render_data_{m_vertices, parent->globalTransform(), texture().get(),
                 shader().get()}
{}

Renderizable::~Renderizable() = default;

Renderizable::RenderizableInternalData Renderizable::getMomentumInternalData()
    const
{
    return {figType(), box(),         color(),   pointCount(),
            shader(),  textureRect(), texture(), color_modifier()};
}

void Renderizable::render()
{
    if (visible())
    {
        update();

        if (!m_vertices.empty())
        {
            sys::getSystem<sys::RenderSystem>(parent()).draw(render_data_);
        }
    }
}

void Renderizable::setTextureAndTextureRect(sptr<res::ITexture> texture_,
                                            const Rectf32& textRect)
{
    textureRect = static_cast<Rects32>(textRect);
    texture.set(std::move(texture_));
}

void Renderizable::setTextureFill(sptr<res::ITexture> texture_)
{
    setTextureAndTextureRect(texture_, textureFillQuad(texture_));
}

void Renderizable::update()
{
    if (ps_readResetHasAnyChanged(box, figType, pointCount))
    {
        updateGeometry();
        textureRect.resetHasChanged();
        color.resetHasChanged();
        color_modifier.resetHasChanged();
    }

    if (ps_readResetHasAnyChanged(textureRect))
    {
        updateTextureCoordsAndColor(m_vertices.verticesArray(),
                                    getMomentumInternalData());
        color.resetHasChanged();
        color_modifier.resetHasChanged();
    }

    if (ps_readResetHasAnyChanged(color, color_modifier))
    {
        updateColors(m_vertices.verticesArray(), getMomentumInternalData());
    }

    if (ps_readResetHasChanged(texture))
    {
        render_data_.texture = texture().get();
    }

    if (ps_readResetHasChanged(shader))
    {
        render_data_.shader = shader().get();
    }
}

void Renderizable::updateGeometry()
{
    if (pointCount())
    {
        const Rectf32& cBox{box()};
        auto& vertices(m_vertices.verticesArray());

        const auto fig_type{figType()};
        const size_type nPoints{pointCount()};
        const size_type nVertex{
            initDataVertexPerFigureAndNumPoints(fig_type, nPoints).second};
        const vector2df radius{cBox.size() / 2.0F};

        vertices.resize(nVertex);  // + 2 for center and repeated first point
        const f64 baseAngle(PiM2Constant<f64> / static_cast<f64>(nPoints));
        const auto leftTop(cBox.leftTop());
        const auto base_position{leftTop + radius};

        auto const& iData{getMomentumInternalData()};

        switch (fig_type)
        {
            case FigType_t::Quad:
            case FigType_t::Shape:
            {
                const auto vertices_iterator_begin = vertices.begin();
                auto vertices_iterator_second      = vertices_iterator_begin;
                auto vertices_iterator{++vertices_iterator_second};
                auto angle{0.0};

                for (size_type i{0U}; i < nPoints; ++i, ++vertices_iterator)
                {
                    angle += baseAngle;
                    const vector2dd r{
                        getPositionFromAngleAndRadius(fig_type, angle, radius)};
                    vertices_iterator->position =
                        base_position + static_cast<vector2df>(r);
                    updateTextureCoordsAndColorForVertex(vertices_iterator,
                                                         iData);
                }

                vertices_iterator->position =
                    vertices_iterator_second->position;
                updateTextureCoordsAndColorForVertex(vertices_iterator, iData);
                vertices_iterator_begin->position = radius + leftTop;
                updateTextureCoordsAndColorForVertex(vertices_iterator_begin,
                                                     iData);
            }
            break;
            case FigType_t::EmptyQuad:
            {
                vertices[0U].position = cBox.leftTop();
                updateTextureCoordsAndColorForVertex(&vertices[0U], iData);
                vertices[1U].position = cBox.rightTop();
                updateTextureCoordsAndColorForVertex(&vertices[1U], iData);
                vertices[2U].position = cBox.rightBottom();
                updateTextureCoordsAndColorForVertex(&vertices[2U], iData);
                vertices[3U].position = cBox.leftBottom();
                updateTextureCoordsAndColorForVertex(&vertices[3U], iData);
                vertices[4U].position = cBox.leftTop();
                updateTextureCoordsAndColorForVertex(&vertices[4U], iData);
            }
            break;
        }
    }
}
}  // namespace haf::scene

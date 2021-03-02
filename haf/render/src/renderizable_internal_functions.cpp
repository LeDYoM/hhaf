#include <render/i_include/renderizable_internal_functions.hpp>
#include <haf/render/include/geometry_math.hpp>

using namespace htps;

namespace haf::scene
{
vector2dd getPositionFromAngleAndRadius(const FigType_t fig_type,
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

/**
 * @brief Get the init data for a vertex array
 *
 * @param fig_type Figure type to create
 * @param num_points Initial number of points
 * @return pair<PrimitiveType, size_type> Initialization data for a vertex
 * array
 */
pair<PrimitiveType, size_type> initDataVertexPerFigureAndNumPoints(
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

Rects32 textureFillQuad(const sptr<res::ITexture>& texture) noexcept
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

void updateGeometry(BasicVertexArray& vertices,
                    Renderizable::RenderizableInternalData const& data)
{
    if (data.pointCount > 0U)
    {
        const vector2df radius{data.box.size() / 2.0F};

        vertices.resize(
            initDataVertexPerFigureAndNumPoints(data.figType, data.pointCount)
                .second);
        const f64 baseAngle(PiM2Constant<f64> /
                            static_cast<f64>(data.pointCount));
        const auto base_position{data.box.leftTop() + radius};

        switch (data.figType)
        {
            case FigType_t::Quad:
            case FigType_t::Shape:
            {
                const auto vertices_iterator_begin = vertices.begin();
                auto vertices_iterator_second      = vertices_iterator_begin;
                auto vertices_iterator{++vertices_iterator_second};
                auto angle{0.0};

                for (size_type i{0U}; i < data.pointCount;
                     ++i, ++vertices_iterator)
                {
                    angle += baseAngle;
                    vertices_iterator->position = base_position +
                        static_cast<vector2df>(getPositionFromAngleAndRadius(
                            data.figType, angle, radius));
                    updateTextureCoordsAndColorForVertex(vertices_iterator,
                                                         data);
                }

                vertices_iterator->position =
                    vertices_iterator_second->position;
                updateTextureCoordsAndColorForVertex(vertices_iterator, data);
                vertices_iterator_begin->position = radius + data.box.leftTop();
                updateTextureCoordsAndColorForVertex(vertices_iterator_begin,
                                                     data);
            }
            break;
            case FigType_t::EmptyQuad:
            {
                vertices[0U].position = data.box.leftTop();
                updateTextureCoordsAndColorForVertex(&vertices[0U], data);
                vertices[1U].position = data.box.rightTop();
                updateTextureCoordsAndColorForVertex(&vertices[1U], data);
                vertices[2U].position = data.box.rightBottom();
                updateTextureCoordsAndColorForVertex(&vertices[2U], data);
                vertices[3U].position = data.box.leftBottom();
                updateTextureCoordsAndColorForVertex(&vertices[3U], data);
                vertices[4U].position = data.box.leftTop();
                updateTextureCoordsAndColorForVertex(&vertices[4U], data);
            }
            break;
        }
    }
}
}  // namespace haf::scene

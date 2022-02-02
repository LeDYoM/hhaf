#include "renderizable_internal_functions.hpp"
#include "geometry_math.hpp"

using namespace htps;

namespace haf::render
{
vector2dd getPositionFromAngleAndRadius(FigType_t const fig_type,
                                        f64 const angle,
                                        vector2df const& radius)
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

pair<PrimitiveType const, size_type const> initDataVertexPerFigureAndNumPoints(
    FigType_t const fig_type,
    size_type const num_points) noexcept
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

Rects32 textureFillQuad(sptr<res::ITexture const> const& texture) noexcept
{
    return texture ? Rects32{0, 0, static_cast<vector2ds32>(texture->size())}
                   : Rects32{};
}

vector2df normalizeInBox(vector2df const& position,
                         RenderizableInternalData const& data) noexcept
{
    f32 const xratio{(position.x - data.box.left) / data.box.width};
    f32 const yratio{(position.y - data.box.top) / data.box.height};
    return {(data.textureRect.left + (data.textureRect.width * xratio)),
            (data.textureRect.top + (data.textureRect.height * yratio))};
}

void updateColorForVertex(RenderizableInternalData const& data,
                          BasicVertexArray::value_type& vertex)
{
    scene::Color dest_color{data.color};
    if (data.color_modifier)
    {
        RenderizableModifierContext const context{
            data.box, data.textureRect,
            data.texture ? data.texture->size() : vector2du32{0U, 0U}, vertex};
        dest_color *= data.color_modifier(context);
    }
    vertex.color = dest_color;
}

void updateColors(BasicVertexArray& vertices,
                  RenderizableInternalData const& data)
{
    for (auto& vertex : vertices)
    {
        updateColorForVertex(data, vertex);
    }
}

void updateTextureCoordsAndColorForVertex(
    BasicVertexArray::iterator const v_iterator,
    RenderizableInternalData const& iData)
{
    auto& dest_vertex     = *v_iterator;
    dest_vertex.texCoords = normalizeInBox(dest_vertex.position, iData);
    updateColorForVertex(iData, dest_vertex);
}

void updateTextureCoordsAndColor(BasicVertexArray& vertices,
                                 RenderizableInternalData const& data)
{
    for (auto& vertex : vertices)
    {
        updateTextureCoordsAndColorForVertex(&vertex, data);
    }
}

void updateGeometry(BasicVertexArray& vertices,
                    RenderizableInternalData const& data)
{
    if (data.pointCount > 0U)
    {
        vector2df const radius{data.box.size() / 2.0F};

        vertices.resize(
            initDataVertexPerFigureAndNumPoints(data.figType, data.pointCount)
                .second);
        const auto baseAngle{PiM2Constant<f64> /
                             static_cast<f64>(data.pointCount)};
        const auto base_position{data.box.leftTop() + radius};

        switch (data.figType)
        {
            case FigType_t::Quad:
            case FigType_t::Shape:
            {
                const auto vertices_iterator_begin = vertices.begin();
                auto vertices_iterator_second{vertices_iterator_begin};
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
}  // namespace haf::render

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
        case FigType_t::Sprite:
        {
            return {PrimitiveType::Triangles, num_points + 2U};
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

void setColor(BasicVertexArray& vertices, scene::Color const& color)
{
    for (auto&& vertex : vertices)
    {
        vertex.color = color;
    }
}
/*
vector2df normalizeInBoxSprite(vector2df const& position,
                         Rectf32 const& textureRect) noexcept
{
    f32 const xratio{(position.x - data.box.left) / data.box.width};
    f32 const yratio{(position.y - data.box.top) / data.box.height};
    return {(data.textureRect.left + (data.textureRect.width * xratio)),
            (data.textureRect.top + (data.textureRect.height * yratio))};
}
*/
void setTextureRect(BasicVertexArray& vertices, Rectf32 const& texture_rect)
{
    vector2df const position{texture_rect.leftTop()};
    vector2df const size{texture_rect.size()};

    for (auto&& vertex : vertices)
    {
        vertex.texCoords = position + (vertex.texCoords * size);
    }
}

void setSize(BasicVertexArray& vertices, vector2df const& size)
{
    for (auto&& vertex : vertices)
    {
        vertex.position *= size;
    }
}

constexpr vector2df defaultLeftBottomPosition{-0.5F, 0.5F};
constexpr vector2df defaultRightBottomPosition{0.5F, 0.5F};
constexpr vector2df defaultLeftTopPosition{-0.5F, -0.5F};
constexpr vector2df defaultRightTopPosition{0.5F, -0.5F};

constexpr vector2df defaultLeftBottomTexture{defaultLeftBottomPosition +
                                             vector2df{0.5F, 0.5F}};
constexpr vector2df defaultRightBottomTexture{defaultRightBottomPosition +
                                              vector2df{0.5F, 0.5F}};
constexpr vector2df defaultLeftTopTexture{defaultLeftTopPosition +
                                          vector2df{0.5F, 0.5F}};
constexpr vector2df defaultRightTopTexture{defaultRightTopPosition +
                                           vector2df{0.5F, 0.5F}};

void setQuad(BasicVertexArray& vertices)
{
    using namespace scene;
    static Vertex quad_vertex_buffer[] = {
        Vertex{defaultLeftBottomPosition, colors::White,
               defaultLeftBottomTexture},
        Vertex{defaultRightBottomPosition, colors::White,
               defaultRightBottomTexture},
        Vertex{defaultLeftTopPosition, colors::White, defaultLeftTopTexture},

        Vertex{defaultLeftTopPosition, colors::White, defaultLeftTopTexture},
        Vertex{defaultRightBottomPosition, colors::White,
               defaultRightBottomTexture},
        Vertex{defaultRightTopPosition, colors::White, defaultRightTopTexture}};

    constexpr fast_u32 kNumSizes{3U * 2U};  // 3 vertex * 2 triangles
    vertices.resize(kNumSizes);
    for (fast_u32 index{0U}; index < kNumSizes; ++index)
    {
        vertices[index] = quad_vertex_buffer[index];
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
            case FigType_t::Sprite:
            {
                auto size{data.box.size()};
                setQuad(vertices);
                setSize(vertices, size);
                setTextureRect(vertices, data.textureRect);
                setColor(vertices, data.color);
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

#include "renderizable.hpp"
#include <lib/render/i_include/rendersystem.hpp>

#include <lib/render/include/renderdata.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/resources/include/ishader.hpp>
#include <lib/system/i_include/get_system.hpp>

#include "geometry_math.hpp"

namespace lib::scene
{
namespace
{
constexpr mtps::vector2dd getPositionFromAngleAndRadius(
    const FigType_t fig_type,
    const mtps::f64 angle,
    const mtps::vector2df& radius)
{
    switch (fig_type)
    {
    default:
    case FigType_t::Quad: {
        return {(sgn_cos(angle) * radius.x), sgn_sin(angle) * radius.y};
    }
    break;
    case FigType_t::Shape: {
        return {std::cos(angle) * radius.x, std::sin(angle) * radius.y};
    }
    }
}

constexpr mtps::pair<PrimitiveType, mtps::size_type>
initDataVertexPerFigureAndNumPoints(const FigType_t fig_type,
                                    const mtps::size_type num_points) noexcept
{
    switch (fig_type)
    {
    default:
    case FigType_t::Quad:
    case FigType_t::Shape: {
        return {PrimitiveType::TriangleFan, num_points + 2U};
    }
    break;
    case FigType_t::EmptyQuad: {
        return {PrimitiveType::LineStrip, num_points + 1U};
    }
    break;
    }
}

mtps::Rects32 textureFillQuad(const mtps::sptr<ITexture>& texture)
{
    return texture
        ? mtps::Rects32{0, 0, static_cast<mtps::vector2ds32>(texture->size())}
        : mtps::Rects32{};
}

}  // namespace

Renderizable::Renderizable(mtps::rptr<SceneNode> parent,
                           mtps::str name,
                           FigType_t figure_type,
                           mtps::size_type initial_point_count,
                           mtps::Rectf32 _box,
                           Color _color,
                           mtps::sptr<ITexture> _texture,
                           mtps::sptr<IShader> _shader) :
    sys::HasName{std::move(name)},
    parent_{std::move(parent)},
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

void Renderizable::render()
{
    if (visible())
    {
        update();

        if (!m_vertices.empty())
        {
            sys::getSystem<sys::RenderSystem>(parent_).draw(render_data_);
        }
    }
}

void Renderizable::setTextureAndTextureRect(mtps::sptr<ITexture> texture_,
                                            const mtps::Rectf32& textRect)
{
    textureRect = static_cast<mtps::Rects32>(textRect);
    texture.set(std::move(texture_));
}

void Renderizable::setTextureFill(mtps::sptr<ITexture> texture_)
{
    setTextureAndTextureRect(texture_, textureFillQuad(texture_));
}

mtps::vector2df Renderizable::normalizeInBox(const mtps::vector2df& position,
                                             const mtps::Rectf32 box,
                                             const mtps::Rectf32& rect) const
{
    const mtps::f32 xratio{(position.x - box.left) / box.width};
    const mtps::f32 yratio{(position.y - box.top) / box.height};
    return {(rect.left + (rect.width * xratio)),
            (rect.top + (rect.height * yratio))};
}

void Renderizable::updateTextureCoordsAndColorForVertex(
    const BasicVertexArray::iterator v_iterator,
    const mtps::Rectf32& cbox,
    const mtps::Rects32& ctexture_rect)
{
    auto& dest_vertex = *v_iterator;
    dest_vertex.texCoords =
        normalizeInBox(dest_vertex.position, cbox, ctexture_rect);
    updateColorForVertex(v_iterator, cbox, ctexture_rect);
}

void Renderizable::updateColorForVertex(
    const BasicVertexArray::iterator v_iterator,
    const mtps::Rectf32& cbox,
    const mtps::Rects32& ctexture_rect)
{
    Color dest_color{color()};
    if (color_modifier())
    {
        RenderizableModifierContext context{
            box(), ctexture_rect,
            texture() ? texture()->size() : mtps::vector2du32{0U, 0U},
            *v_iterator};
        dest_color *= color_modifier()(context);
    }
    v_iterator->color = dest_color;
}

void Renderizable::updateTextureCoordsAndColor()
{
    const auto& cbox(box());
    const auto ctexture_rect{textureRect()};

    BasicVertexArray& vertices{m_vertices.verticesArray()};

    for (auto v_iterator = vertices.begin(); v_iterator != vertices.end();
         ++v_iterator)
    {
        updateTextureCoordsAndColorForVertex(v_iterator, cbox, ctexture_rect);
    }
}

void Renderizable::updateColors()
{
    const auto& cbox(box());
    const auto ctexture_rect{textureRect()};

    BasicVertexArray& vertices{m_vertices.verticesArray()};

    for (auto v_iterator = vertices.begin(); v_iterator != vertices.end();
         ++v_iterator)
    {
        updateColorForVertex(v_iterator, cbox, ctexture_rect);
    }
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
        updateTextureCoordsAndColor();
        color.resetHasChanged();
        color_modifier.resetHasChanged();
    }

    if (ps_readResetHasAnyChanged(color, color_modifier))
    {
        updateColors();
    }

    if (ps_readResetHasChanged(texture))
    {
        //        render_data_.texture = (texture().get() != nullptr) ?
        //        (dynamic_cast<Texture *>(texture().get())) : nullptr;
        render_data_.texture = texture().get();
    }

    if (ps_readResetHasChanged(shader))
    {
        //        render_data_.shader = (shader().get() != nullptr) ?
        //        (dynamic_cast<Shader *>(shader().get())) : nullptr;
        render_data_.shader = shader().get();
    }
}

void Renderizable::updateGeometry()
{
    if (pointCount())
    {
        const mtps::Rectf32& cBox{box()};
        auto& vertices(m_vertices.verticesArray());

        const auto fig_type{figType()};
        const mtps::size_type nPoints{pointCount()};
        const mtps::size_type nVertex{
            initDataVertexPerFigureAndNumPoints(fig_type, nPoints).second};
        const mtps::vector2df radius{cBox.size() / 2.0F};

        vertices.resize(nVertex);  // + 2 for center and repeated first point
        const mtps::f64 baseAngle(PiM2Constant<mtps::f64> /
                                  static_cast<mtps::f64>(nPoints));
        const auto leftTop(cBox.leftTop());
        const auto base_position{leftTop + radius};

        switch (fig_type)
        {
        case FigType_t::Quad:
        case FigType_t::Shape: {
            const auto vertices_iterator_begin =
                m_vertices.verticesArray().begin();
            auto vertices_iterator_second = vertices_iterator_begin;
            auto vertices_iterator{++vertices_iterator_second};
            auto angle{0.0};

            for (mtps::size_type i{0U}; i < nPoints; ++i, ++vertices_iterator)
            {
                angle += baseAngle;
                const mtps::vector2dd r{
                    getPositionFromAngleAndRadius(fig_type, angle, radius)};
                vertices_iterator->position =
                    base_position + static_cast<mtps::vector2df>(r);
                updateTextureCoordsAndColorForVertex(vertices_iterator, cBox,
                                                     textureRect());
            }

            vertices_iterator->position = vertices_iterator_second->position;
            updateTextureCoordsAndColorForVertex(vertices_iterator, cBox,
                                                 textureRect());
            vertices_iterator_begin->position = radius + leftTop;
            updateTextureCoordsAndColorForVertex(vertices_iterator_begin, cBox,
                                                 textureRect());
        }
        break;
        case FigType_t::EmptyQuad: {
            auto& vertices        = m_vertices.verticesArray();
            vertices[0U].position = cBox.leftTop();
            updateTextureCoordsAndColorForVertex(&vertices[0U], cBox,
                                                 textureRect());
            vertices[1U].position = cBox.rightTop();
            updateTextureCoordsAndColorForVertex(&vertices[1U], cBox,
                                                 textureRect());
            vertices[2U].position = cBox.rightBottom();
            updateTextureCoordsAndColorForVertex(&vertices[2U], cBox,
                                                 textureRect());
            vertices[3U].position = cBox.leftBottom();
            updateTextureCoordsAndColorForVertex(&vertices[3U], cBox,
                                                 textureRect());
            vertices[4U].position = cBox.leftTop();
            updateTextureCoordsAndColorForVertex(&vertices[4U], cBox,
                                                 textureRect());
        }
        break;
        }
    }
}
}  // namespace lib::scene

#include "renderizable.hpp"
#include <lib/system/rendersystem.hpp>

#include <lib/scene/scenemanager.hpp>
#include <lib/scene/renderdata.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/resources/texture.hpp>
#include <lib/system/systemprovider.hpp>

#include "geometry_math.hpp"

namespace lib::scene
{
namespace
{
template <typename T>
constexpr int sgn(const T val) noexcept
{
    return (T(0) < val) - (val < T(0));
}

template <typename T>
constexpr int sgn_cos(T angle)
{
    return sgn(std::cos(angle));
}

template <typename T>
constexpr int sgn_sin(T angle)
{
    return sgn(std::sin(angle));
}

constexpr vector2dd getPositionFromAngleAndRadius(const FigType_t fig_type,
                                                  const f64 angle, const vector2df &radius)
{
    switch (fig_type)
    {
    default:
    case FigType_t::Quad:
    {
        return {(sgn_cos(angle) * radius.x),
                sgn_sin(angle) * radius.y};
    }
    break;
    case FigType_t::Shape:
    {
        return {std::cos(angle) * radius.x,
                std::sin(angle) * radius.y};
    }
    }
}

} // namespace

Renderizable::Renderizable(SceneNode *const parent, str name, const u32 vertexCount)
    : core::HasName{std::move(name)},
      parent_{parent},
      m_vertices{TriangleFan, vertexCount}
{
}

Renderizable::~Renderizable() = default;

void Renderizable::render()
{
    if (visible())
    {
        update();

        if (!m_vertices.empty())
        {
            parent_->parentScene()->sceneManager().systemProvider().renderSystem().draw(scene::RenderData{
                m_vertices,
                parent_->globalTransform(),
                dynamic_cast<Texture *>(texture().get())});
        }
    }
}

void Renderizable::setTextureAndTextureRect(sptr<ITexture> texture_, const Rectf32 &textRect)
{
    texture.set(texture_);
    if (texture_)
    {
        textureRect = static_cast<Rects32>(textRect);
    }
}

void Renderizable::setTextureFill(sptr<ITexture> texture_)
{
    if (texture_)
    {
        setTextureAndTextureRect(std::move(texture_),
                                 {0.0f, 0.0f, static_cast<vector2df>(texture_->size())});
    }
}

Rectf32 Renderizable::normalizedTextureRect() const
{
    const auto texture_rectf32{static_cast<Rectf32>(textureRect())};
    const auto texture_sizef32{static_cast<vector2df>(texture()->size())};

    return Rectf32 {
        texture_rectf32.leftTop() / texture_sizef32,
        texture_rectf32.size() / texture_sizef32};
}

void Renderizable::updateTextureCoordsAndColorForVertex(
    const BasicVertexArray::iterator v_iterator,
    const Rectf32 &cbox, const Rects32 &ctexture_rect)
{
    auto &dest_vertex = *v_iterator;
    const f32 xratio{(dest_vertex.position.x - cbox.left) / cbox.width};
    const f32 yratio{(dest_vertex.position.y - cbox.top) / cbox.height};
    dest_vertex.texCoords = {(ctexture_rect.left + (ctexture_rect.width * xratio)),
                             (ctexture_rect.top + (ctexture_rect.height * yratio))};

    updateColorForVertex(v_iterator, cbox, ctexture_rect);
}

void Renderizable::updateColorForVertex(
    const BasicVertexArray::iterator v_iterator,
    const Rectf32 &cbox, const Rects32 &ctexture_rect)
{
    Color dest_color{color()};
    if (color_modifier())
    {
        dest_color *= color_modifier()(v_iterator, cbox, ctexture_rect);
    }
    v_iterator->color = dest_color;    
}

void Renderizable::updateTextureCoordsAndColor()
{
    const auto &cbox(box());
    const auto ctexture_rect{textureRect()};

    BasicVertexArray &vertices{m_vertices.verticesArray()};

    for (auto v_iterator = vertices.begin();
         v_iterator != vertices.end(); ++v_iterator)
    {
        updateTextureCoordsAndColorForVertex(v_iterator, cbox, ctexture_rect);
    }
}

void Renderizable::updateColors()
{
    const auto &cbox(box());
    const auto ctexture_rect{textureRect()};

    BasicVertexArray &vertices{m_vertices.verticesArray()};

    for (auto v_iterator = vertices.begin();
         v_iterator != vertices.end(); ++v_iterator)
    {
        updateColorForVertex(v_iterator, cbox, ctexture_rect);
    }
}

void Renderizable::update()
{
    if (ps_readResetHasAnyChanged(box, figType))
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
}

void Renderizable::updateGeometry()
{
    if (pointCount())
    {
        const Rectf32 &cBox{box()};
        auto &vertices(m_vertices.verticesArray());

        const size_type nPoints{pointCount()};
        const size_type nVertex{nPoints + 2};
        const vector2df radius{cBox.size() / 2.0F};

        vertices.resize(nVertex); // + 2 for center and repeated first point
        const f64 baseAngle(PiM2Constant<f64> / static_cast<f64>(nPoints));
        const auto leftTop(cBox.leftTop());
        const auto base_position{leftTop + radius};
        const auto fig_type{figType()};

        const auto vertices_iterator_begin = m_vertices.verticesArray().begin();
        auto vertices_iterator_second = vertices_iterator_begin;
        auto vertices_iterator{++vertices_iterator_second};
        auto angle{0.0};

        for (size_type i{0U}; i < nPoints; ++i, ++vertices_iterator)
        {
            angle += baseAngle;
            const vector2dd r{getPositionFromAngleAndRadius(fig_type, angle, radius)};
            vertices_iterator->position = base_position + static_cast<vector2df>(r);
            updateTextureCoordsAndColorForVertex(vertices_iterator, cBox, textureRect());
        }

        vertices_iterator->position = vertices_iterator_second->position;
        updateTextureCoordsAndColorForVertex(vertices_iterator, cBox, textureRect());
        vertices_iterator_begin->position = radius + leftTop;
        updateTextureCoordsAndColorForVertex(vertices_iterator_begin, cBox, textureRect());
    }
}
} // namespace lib::scene

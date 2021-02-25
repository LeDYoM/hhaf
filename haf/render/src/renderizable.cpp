#include <haf/render/include/renderizable.hpp>

#include <render/i_include/rendersystem.hpp>
#include <render/i_include/renderizable_internal_data.hpp>
#include <system/i_include/get_system.hpp>

#include <haf/render/include/renderdata.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/render/include/renderizable_builder.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ishader.hpp>
#include <haf/render/include/vertexarray.hpp>
#include <haf/render/include/renderdata.hpp>
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

void updateGeometry(BasicVertexArray& vertices,
                    Renderizable::RenderizableInternalData const& data)
{
    if (data.pointCount > 0U)
    {
        const auto fig_type{data.figType};
        const size_type nPoints{data.pointCount};
        const size_type nVertex{
            initDataVertexPerFigureAndNumPoints(fig_type, nPoints).second};
        const vector2df radius{data.box.size() / 2.0F};

        vertices.resize(nVertex);  // + 2 for center and repeated first point
        const f64 baseAngle(PiM2Constant<f64> / static_cast<f64>(nPoints));
        const auto leftTop(data.box.leftTop());
        const auto base_position{leftTop + radius};

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
                                                         data);
                }

                vertices_iterator->position =
                    vertices_iterator_second->position;
                updateTextureCoordsAndColorForVertex(vertices_iterator, data);
                vertices_iterator_begin->position = radius + leftTop;
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

}  // namespace

struct Renderizable::RenderizablePrivate
{
    VertexArray vertices_;
    RenderData render_data_;
    rptr<Renderizable const> const i_this_;

    RenderizablePrivate(FigType_t const figure_type,
                        size_type const initial_point_count,
                        Matrix4x4 const& matrix,
                        rptr<res::ITexture> texture,
                        rptr<res::IShader> shader,
                        rptr<Renderizable const> i_this) :
        vertices_{initDataVertexPerFigureAndNumPoints(figure_type,
                                                      initial_point_count)},
        render_data_{vertices_, matrix, texture, shader},
        i_this_{std::move(i_this)}
    {}

    Renderizable::RenderizableInternalData getMomentumInternalData() const
    {
        return {i_this_->figType(), i_this_->box(),
                i_this_->color(),   i_this_->pointCount(),
                i_this_->shader(),  i_this_->textureRect(),
                i_this_->texture(), i_this_->color_modifier()};
    }
};

Renderizable::Renderizable(rptr<SceneNode> _parent,
                           str name,
                           FigType_t const figure_type,
                           size_type const initial_point_count,
                           Rectf32 _box,
                           Color _color,
                           sptr<res::ITexture> _texture,
                           sptr<res::IShader> _shader) :
    sys::HasName{std::move(name)},
    SceneNodeParent{_parent},
    p_{make_pimplp<RenderizablePrivate>(figure_type,
                                        initial_point_count,
                                        parent()->globalTransform(),
                                        texture().get(),
                                        shader().get(), this)},
    figType{figure_type},
    pointCount{initial_point_count},
    box{std::move(_box)},
    color{std::move(_color)},
    shader{std::move(_shader)},
    textureRect{textureFillQuad(_texture)},
    texture{std::move(_texture)}
{}

Renderizable::~Renderizable() = default;

void Renderizable::render()
{
    if (visible())
    {
        update();

        if (!p_->vertices_.empty())
        {
            sys::getSystem<sys::RenderSystem>(parent()).draw(p_->render_data_);
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
    auto const& mi_data{p_->getMomentumInternalData()};

    if (ps_readResetHasAnyChanged(box, figType, pointCount))
    {
        updateGeometry(p_->vertices_.verticesArray(), mi_data);
        textureRect.resetHasChanged();
        color.resetHasChanged();
        color_modifier.resetHasChanged();
    }

    if (ps_readResetHasAnyChanged(textureRect))
    {
        updateTextureCoordsAndColor(p_->vertices_.verticesArray(), mi_data);
        color.resetHasChanged();
        color_modifier.resetHasChanged();
    }

    if (ps_readResetHasAnyChanged(color, color_modifier))
    {
        updateColors(p_->vertices_.verticesArray(), mi_data);
    }

    if (ps_readResetHasChanged(texture))
    {
        p_->render_data_.texture = texture().get();
    }

    if (ps_readResetHasChanged(shader))
    {
        p_->render_data_.shader = shader().get();
    }
}

}  // namespace haf::scene

#include <haf/include/render/renderizable.hpp>

#include "rendersystem.hpp"
#include "renderizable_internal_data.hpp"
#include "renderizable_internal_functions.hpp"
#include "system/get_system.hpp"

#include <haf/include/render/renderdata.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include <haf/include/render/vertexarray.hpp>
#include <haf/include/render/renderdata.hpp>

using namespace htps;
using namespace haf::render;

namespace haf::scene
{

struct Renderizable::RenderizablePrivate
{
    rptr<SceneNode> m_parent;
    VertexArray vertices_;
    RenderData render_data_;
    rptr<Renderizable const> const i_this_;

    RenderizablePrivate(rptr<SceneNode> parent,
                        FigType_t const figure_type,
                        size_type const initial_point_count,
                        Matrix4x4 const& matrix,
                        rptr<res::ITexture> texture,
                        rptr<res::IShader> shader,
                        rptr<Renderizable const> i_this) :
                        m_parent{parent},
        vertices_{render::initDataVertexPerFigureAndNumPoints(figure_type,
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

Renderizable::Renderizable(rptr<SceneNode> parent,
                           str name,
                           FigType_t const figure_type,
                           size_type const initial_point_count,
                           Rectf32 _box,
                           Color _color,
                           sptr<res::ITexture> _texture,
                           sptr<res::IShader> _shader) :
    sys::HasName{std::move(name)},
    figType{figure_type},
    box{std::move(_box)},
    color{std::move(_color)},
    pointCount{initial_point_count},
    shader{std::move(_shader)},
    p_{make_pimplp<RenderizablePrivate>(parent,
                                        figure_type,
                                        initial_point_count,
                                        parent->globalTransform(),
                                        texture().get(),
                                        shader().get(),
                                        this)},
    textureRect{render::textureFillQuad(_texture)},
    texture{std::move(_texture)}
{}

Renderizable::~Renderizable() = default;

htps::rptr<SceneNode> Renderizable::parent() noexcept
{
    return p_->m_parent;
}

htps::rptr<SceneNode const> Renderizable::parent() const noexcept
{
    return p_->m_parent;
}

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
    setTextureAndTextureRect(texture_, render::textureFillQuad(texture_));
}

void Renderizable::update()
{
    auto const& mi_data{p_->getMomentumInternalData()};

    if (ps_readResetHasAnyChanged(box, figType, pointCount))
    {
        render::updateGeometry(p_->vertices_.verticesArray(), mi_data);
        textureRect.resetHasChanged();
        color.resetHasChanged();
        color_modifier.resetHasChanged();
    }

    if (ps_readResetHasAnyChanged(textureRect))
    {
        render::updateTextureCoordsAndColor(p_->vertices_.verticesArray(), mi_data);
        color.resetHasChanged();
        color_modifier.resetHasChanged();
    }

    if (ps_readResetHasAnyChanged(color, color_modifier))
    {
        render::updateColors(p_->vertices_.verticesArray(), mi_data);
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

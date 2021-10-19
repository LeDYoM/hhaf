#include <haf/include/render/renderizable.hpp>

#include "rendersystem.hpp"
#include "renderizable_internal_data.hpp"
#include "renderizable_internal_functions.hpp"
#include "system/get_system.hpp"

#include <haf/include/render/renderdata.hpp>
#include <haf/include/scene/transformable_scene_node.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include <haf/include/render/vertexarray.hpp>
#include <haf/include/render/renderdata.hpp>

using namespace htps;
using namespace haf::scene;

namespace haf::render
{

struct Renderizable::RenderizablePrivate
{
    rptr<TransformableSceneNode> parent_;
    VertexArray vertices_;
    RenderData render_data_;
    rptr<Renderizable const> const i_this_;

    RenderizablePrivate(rptr<TransformableSceneNode> parent,
                        FigType_t const figure_type,
                        size_type const initial_point_count,
                        Matrix4x4 const& matrix,
                        rptr<res::ITexture> texture,
                        rptr<res::IShader> shader,
                        rptr<Renderizable const> i_this) :
        parent_{parent},
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

Renderizable::Renderizable(rptr<TransformableSceneNode> parent,
                           RenderizableData&& renderizable_data) :
    sys::HasName{std::move(renderizable_data.prop<RenderizableName>()())},
    figType{renderizable_data.prop<FigureTypeProperty>()()},
    box{renderizable_data.prop<RenderizableSceneBoxProperty>()()},
    color{renderizable_data.prop<ColorProperty>()()},
    pointCount{renderizable_data.prop<PointCount>()()},
    shader{renderizable_data.prop<ShaderProperty>()()},
    p_{make_pimplp<RenderizablePrivate>(
        parent,
        renderizable_data.prop<FigureTypeProperty>()(),
        renderizable_data.prop<PointCount>()(),
        parent->globalTransform(),
        renderizable_data.prop<TextureProperty>()().get(),
        renderizable_data.prop<ShaderProperty>()().get(),
        this)},
    textureRect{textureFillQuad(renderizable_data.prop<TextureProperty>()())},
    texture{renderizable_data.prop<TextureProperty>()()},
    color_modifier{renderizable_data.prop<ColorModifierProperty>()()}
{}

Renderizable::~Renderizable() = default;

rptr<TransformableSceneNode> Renderizable::parent() noexcept
{
    return p_->parent_;
}

rptr<TransformableSceneNode const> Renderizable::parent() const noexcept
{
    return p_->parent_;
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

void Renderizable::setTextureAndTextureRectFromTextureSize(sptr<res::ITexture> texture_,
                                            const Rectf32& textRect) noexcept
{
    textureRect = static_cast<Rects32>(textRect);
    texture = std::move(texture_);
}

void Renderizable::setTextureFill(sptr<res::ITexture> texture_)
{
    setTextureAndTextureRectFromTextureSize(texture_, textureFillQuad(texture_));
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

}  // namespace haf::render

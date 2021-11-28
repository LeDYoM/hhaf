#include <haf/include/render/renderizable.hpp>
#include "render/renderizable_private.hpp"
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

void Renderizable::setTextureAndTextureRectFromTextureSize(
    sptr<res::ITexture> texture_,
    Rects32 const& textRect) noexcept
{
    textureRect = textRect;
    texture     = std::move(texture_);
}

void Renderizable::setTextureAndTextureRectNormalizedRect(
    sptr<res::ITexture> texture_,
    Rectf32 const& textRect) noexcept
{
    Rects32 dest_textureRect{textRect};
    dest_textureRect.scale(texture_->size());
    textureRect = dest_textureRect;
    texture     = std::move(texture_);
}

void Renderizable::setTextureFill(sptr<res::ITexture> texture_)
{
    setTextureAndTextureRectFromTextureSize(texture_,
                                            textureFillQuad(texture_));
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

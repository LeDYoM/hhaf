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
    p_{make_pimplp<RenderizablePrivate>(
        parent,
        renderizable_data.prop<FigureTypeProperty>()(),
        renderizable_data.prop<PointCount>()(),
        parent->globalTransform(),
        renderizable_data.prop<TextureProperty>()().get(),
        renderizable_data.prop<ShaderProperty>()().get(),
        this)},
    textureRect{textureFillQuad(renderizable_data.prop<TextureProperty>()())},
    texture{renderizable_data.prop<TextureProperty>()()}
{
    prop<PointCount>().set(renderizable_data.prop<PointCount>()());
    prop<FigureTypeProperty>().set(
        renderizable_data.prop<FigureTypeProperty>()());
    prop<BoxProperty>().set(renderizable_data.prop<BoxProperty>()());
    prop<ShaderProperty>().set(renderizable_data.prop<ShaderProperty>()());
    prop<ColorModifierProperty>().set(
        renderizable_data.prop<ColorModifierProperty>()());
    prop<ColorProperty>().set(renderizable_data.prop<ColorProperty>()());
}

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
    // Generate a copy of the texture rect
    auto dest_textureRect{textRect};
    // Scale it according to the size of the current texture
    dest_textureRect.scale(texture_->size());
    // Use it as a new texture rect
    textureRect = std::move(dest_textureRect);
    texture     = std::move(texture_);
}

void Renderizable::setTextureFill(sptr<res::ITexture> texture_)
{
    setTextureAndTextureRectFromTextureSize(std::move(texture_),
                                            textureFillQuad(texture_));
}

void Renderizable::update()
{
    auto const& mi_data{p_->getMomentumInternalData()};

    if (ps_readResetHasAnyChanged(prop<PointCount>(),
                                  prop<FigureTypeProperty>(),
                                  prop<BoxProperty>()))
    {
        updateGeometry(p_->vertices_.verticesArray(), mi_data);
        textureRect.resetHasChanged();
        prop<ColorProperty>().resetHasChanged();
        prop<ColorModifierProperty>().resetHasChanged();
    }
    else if (textureRect.readResetHasChanged())
    {
        updateTextureCoordsAndColor(p_->vertices_.verticesArray(), mi_data);
        prop<ColorProperty>().resetHasChanged();
        prop<ColorModifierProperty>().resetHasChanged();
    }
    else if (ps_readResetHasAnyChanged(prop<ColorProperty>(),
                                       prop<ColorModifierProperty>()))
    {
        updateColors(p_->vertices_.verticesArray(), mi_data);
    }

    if (texture.readResetHasChanged())
    {
        p_->render_data_.texture = texture().get();
    }

    if (prop<ShaderProperty>().readResetHasChanged())
    {
        p_->render_data_.shader = prop<ShaderProperty>()().get();
    }
}

}  // namespace haf::render

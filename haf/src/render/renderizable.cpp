#include <haf/include/render/renderizable.hpp>
#include "render/renderizable_private.hpp"
#include "render_system.hpp"
#include "renderizable_internal_data.hpp"
#include "renderizable_internal_functions.hpp"
#include "system/get_system.hpp"
#include "render_data.hpp"

#include <haf/include/scene/transformable_scene_node.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include <haf/include/render/vertex_array.hpp>

using namespace htps;
using namespace haf::scene;

namespace haf::render
{
Renderizable::Renderizable(rptr<TransformableSceneNode> parent,
                           RenderizableData&& renderizable_data) :
    sys::HasName{std::move(renderizable_data.prop<RenderizableName>()())},
    RenderizableData{std::move(renderizable_data)},
    p_{make_pimplp<RenderizablePrivate>(parent,
                                        prop<FigureTypeProperty>()(),
                                        prop<PointCount>()(),
                                        parent->globalTransform(),
                                        prop<TextureProperty>()().get(),
                                        prop<ShaderProperty>()().get(),
                                        this)}
{
    prop<TextureRectProperty>().set(
        textureFillQuad(renderizable_data.prop<TextureProperty>()()));
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
            p_->updateBackendData();
            sys::getSystem<sys::RenderSystem>(parent()).draw(p_->render_data_);
        }
    }
}

void Renderizable::setTextureAndTextureRectFromTextureSize(
    sptr<res::ITexture> texture_,
    Rects32 const& textRect) noexcept
{
    prop<TextureRectProperty>().set(textRect);
    prop<TextureProperty>().set(std::move(texture_));
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
    setTextureAndTextureRectFromTextureSize(std::move(texture_),
                                            dest_textureRect);
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
        prop<TextureRectProperty>().resetHasChanged();
        prop<ColorProperty>().resetHasChanged();
        prop<ColorModifierProperty>().resetHasChanged();
    }
    else if (prop<TextureRectProperty>().readResetHasChanged())
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

    if (prop<TextureProperty>().readResetHasChanged())
    {
        p_->render_data_.texture = prop<TextureProperty>()().get();
    }

    if (prop<ShaderProperty>().readResetHasChanged())
    {
        p_->render_data_.shader = prop<ShaderProperty>()().get();
    }
}

}  // namespace haf::render

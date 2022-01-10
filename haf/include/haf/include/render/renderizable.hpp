#ifndef HAF_SCENE_RENDERIZABLE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/propertystate.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/p_impl_pointer.hpp>

#include <haf/include/render/renderizable_modifier_context.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/render/renderizable_data.hpp>
#include <haf/include/scene/hasname.hpp>
#include <haf/include/render/fig_type.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>
#include <haf/include/render/renderizable_data.hpp>

namespace haf::scene
{
class TransformableSceneNode;
}

namespace haf::render
{
class Renderizable final : public sys::HasName, public RenderizableData
{
public:
    using RenderizableData::prop;
    using RenderizableData::put;

    Renderizable(htps::rptr<scene::TransformableSceneNode> parent,
                 RenderizableData&& renderizable_data);

    ~Renderizable();

    void render();

    htps::PropertyState<FigType_t> figType;
    htps::PropertyState<htps::Rectf32> box;
    htps::PropertyState<scene::Color> color;
    htps::PropertyState<htps::size_type> pointCount;
    htps::PropertyState<htps::sptr<res::IShader>> shader;

    htps::PropertyState<
        htps::function<scene::Color(RenderizableModifierContext const&)>>
        color_modifier;

    htps::BasicProperty<bool> visible{true};

    void setTextureAndTextureRectFromTextureSize(
        htps::sptr<res::ITexture> texture_,
        htps::Rects32 const& textRect) noexcept;

    void setTextureAndTextureRectNormalizedRect(
        htps::sptr<res::ITexture> texture_,
        htps::Rectf32 const& textRect) noexcept;

    void setTextureFill(htps::sptr<res::ITexture> texture_);

    htps::rptr<scene::TransformableSceneNode> parent() noexcept;
    htps::rptr<scene::TransformableSceneNode const> parent() const noexcept;

    struct RenderizableInternalData;

private:
    struct RenderizablePrivate;
    htps::PImplPointer<RenderizablePrivate> p_;

    htps::PropertyState<htps::Rects32> textureRect;
    htps::PropertyState<htps::sptr<res::ITexture>> texture;

    void update();
};
}  // namespace haf::render

#endif

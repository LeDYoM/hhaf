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
class Renderizable final : public sys::HasName, private RenderizableData
{
public:
    using RenderizableData::prop;
    using RenderizableData::put;

    Renderizable(htps::rptr<scene::TransformableSceneNode> parent,
                 RenderizableData&& renderizable_data);

    ~Renderizable();

    void render(bool const parent_transformation_changed);

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

private:
    struct RenderizablePrivate;
    htps::PImplPointer<RenderizablePrivate> p_;

    void update(bool const parent_transformation_changed);
};
}  // namespace haf::render

#endif

#ifndef HAF_SCENE_RENDERIZABLE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/propertystate.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/p_impl_pointer.hpp>

#include <haf/include/render/renderizable_modifier_context.hpp>
#include <haf/include/scene/color.hpp>
#include <haf/include/scene/hasname.hpp>
#include <haf/include/render/fig_type.hpp>
#include <haf/include/resources/itexture.hpp>
#include <haf/include/resources/ishader.hpp>

namespace haf::scene
{
class TransformableSceneNode;
}

namespace haf::render
{
class Renderizable final : public sys::HasName
{
public:
    Renderizable(htps::rptr<scene::TransformableSceneNode> parent,
                 htps::str name,
                 FigType_t const figure_type,
                 htps::size_type const initial_point_count,
                 htps::Rectf32 _box,
                 scene::Color color,
                 htps::sptr<res::ITexture> _texture,
                 htps::sptr<res::IShader> _shader);

    ~Renderizable();

    void render();

    htps::PropertyState<FigType_t> figType;
    htps::PropertyState<htps::Rectf32> box;
    htps::PropertyState<scene::Color> color;
    htps::PropertyState<htps::size_type> pointCount;
    htps::PropertyState<htps::sptr<res::IShader>> shader;
    htps::PropertyState<
        htps::function<scene::Color(const RenderizableModifierContext&)>>
        color_modifier;

    htps::BasicProperty<bool> visible{true};

    void setTextureAndTextureRect(htps::sptr<res::ITexture> texture_,
                                  const htps::Rectf32& textRect);

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

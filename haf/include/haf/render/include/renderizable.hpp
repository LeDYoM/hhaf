#pragma once

#ifndef HAF_SCENE_RENDERIZABLE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/propertystate.hpp>
#include <mtypes/include/function.hpp>

#include <haf/render/include/renderizable_modifier_context.hpp>
#include <haf/scene/include/color.hpp>
#include <haf/scene/include/hasname.hpp>
#include <haf/render/include/fig_type.hpp>
#include <haf/render/include/vertexarray.hpp>
#include <haf/resources/include/itexture.hpp>
#include <haf/resources/include/ishader.hpp>
#include <haf/render/include/renderdata.hpp>

namespace haf::scene
{
class SceneNode;

class Renderizable final : public sys::HasName
{
public:
    Renderizable(mtps::rptr<SceneNode> parent,
                 mtps::str name,
                 FigType_t figure_type,
                 mtps::size_type initial_point_count,
                 mtps::Rectf32 _box,
                 Color color,
                 mtps::sptr<res::ITexture> _texture,
                 mtps::sptr<res::IShader> _shader);

    ~Renderizable();

    void render();

    mtps::PropertyState<FigType_t> figType;
    mtps::PropertyState<mtps::Rectf32> box;
    mtps::PropertyState<Color> color;
    mtps::PropertyState<mtps::size_type> pointCount;
    mtps::PropertyState<mtps::sptr<res::IShader>> shader;
    mtps::PropertyState<
        mtps::function<Color(const RenderizableModifierContext&)>>
        color_modifier;

    mtps::BasicProperty<bool> visible{true};

    void setTextureAndTextureRect(mtps::sptr<res::ITexture> texture_,
                                  const mtps::Rectf32& textRect);

    void setTextureFill(mtps::sptr<res::ITexture> texture_);

private:
    const mtps::rptr<SceneNode> parent_;

    mtps::PropertyState<mtps::Rects32> textureRect;
    mtps::PropertyState<mtps::sptr<res::ITexture>> texture;

    VertexArray m_vertices;
    RenderData render_data_;

    void updateGeometry();
    void updateTextureCoordsAndColor();
    void updateTextureCoordsAndColorForVertex(
        const BasicVertexArray::iterator v_iterator,
        const mtps::Rectf32& cbox,
        const mtps::Rects32& ctexture_rect);
    void updateColorForVertex(const BasicVertexArray::iterator v_iterator,
                              const mtps::Rectf32& cbox,
                              const mtps::Rects32& ctexture_rect);
    void updateColors();

    mtps::vector2df normalizeInBox(const mtps::vector2df& position,
                                   const mtps::Rectf32 other_box,
                                   const mtps::Rectf32& rect) const;
    void update();
};
}  // namespace haf::scene

#endif

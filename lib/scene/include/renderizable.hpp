#pragma once

#ifndef HAF_SCENE_RENDERIZABLE_INCLUDE_HPP
#define HAF_SCENE_RENDERIZABLE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/include/renderizable_modifier_context.hpp>
#include <lib/scene/include/color.hpp>
#include <lib/scene/include/hasname.hpp>
#include <lib/scene/include/vertexarray.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/resources/include/ishader.hpp>
#include <lib/render/include/renderdata.hpp>

namespace haf::scene
{
class SceneNode;

enum class FigType_t : mtps::u8
{
    Quad,
    Shape,
    EmptyQuad
};

class Renderizable final : public sys::HasName
{
public:
    Renderizable(mtps::rptr<SceneNode> parent, mtps::str name,
                 FigType_t figure_type, mtps::size_type initial_point_count, 
                 mtps::Rectf32 _box, Color color, mtps::sptr<ITexture> _texture,
                 mtps::sptr<IShader> _shader);

    ~Renderizable();

    void render();

    mtps::PropertyState<FigType_t> figType;
    mtps::PropertyState<mtps::Rectf32> box;
    mtps::PropertyState<Color> color;
    mtps::PropertyState<mtps::size_type> pointCount;
    mtps::PropertyState<mtps::sptr<IShader>> shader;
    mtps::PropertyState<mtps::function<Color(const RenderizableModifierContext &)>> color_modifier;

    mtps::BasicProperty<bool> visible{true};

    void setTextureAndTextureRect(mtps::sptr<ITexture> texture_,
                                  const mtps::Rectf32 &textRect);

    void setTextureFill(mtps::sptr<ITexture> texture_);

private:
    const mtps::rptr<SceneNode> parent_;

    mtps::PropertyState<mtps::Rects32> textureRect;
    mtps::PropertyState<mtps::sptr<ITexture>> texture;

    VertexArray m_vertices;
    RenderData render_data_;

    void updateGeometry();
    void updateTextureCoordsAndColor();
    void updateTextureCoordsAndColorForVertex(const BasicVertexArray::iterator v_iterator,
                                              const mtps::Rectf32 &cbox, const mtps::Rects32 &ctexture_rect);
    void updateColorForVertex(const BasicVertexArray::iterator v_iterator,
                              const mtps::Rectf32 &cbox, const mtps::Rects32 &ctexture_rect);
    void updateColors();

    mtps::vector2df normalizeInBox(const mtps::vector2df &position, const mtps::Rectf32 box, const mtps::Rectf32 &rect) const;
    void update();
};
} // namespace haf::scene

#endif

#pragma once

#ifndef LIB_SCENE_RENDERIZABLE_INCLUDE_HPP
#define LIB_SCENE_RENDERIZABLE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/renderizable_modifier_context.hpp>
#include <lib/scene/color.hpp>
#include <lib/scene/hasname.hpp>
#include <lib/scene/vertexarray.hpp>
#include <lib/resources/include/itexture.hpp>
#include <lib/resources/include/ishader.hpp>
#include <lib/scene/renderdata.hpp>

namespace lib::scene
{
class SceneNode;

enum class FigType_t : u8
{
    Quad,
    Shape
};

class Renderizable final : public sys::HasName
{
public:
    Renderizable(rptr<SceneNode> parent, str name,
                 FigType_t figure_type, size_type initial_point_count, 
                 Rectf32 _box, Color color, sptr<ITexture> _texture,
                 sptr<IShader> _shader);

    ~Renderizable();

    void render();

    PropertyState<FigType_t> figType;
    PropertyState<Rectf32> box;
    PropertyState<Color> color;
    PropertyState<size_type> pointCount;
    PropertyState<sptr<IShader>> shader;
    PropertyState<function<Color(const RenderizableModifierContext &)>> color_modifier;

    BasicProperty<bool> visible{true};

    void setTextureAndTextureRect(sptr<ITexture> texture_,
                                  const Rectf32 &textRect);

    void setTextureFill(sptr<ITexture> texture_);

private:
    const rptr<SceneNode> parent_;

    PropertyState<Rects32> textureRect;
    PropertyState<sptr<ITexture>> texture;

    VertexArray m_vertices;
    RenderData render_data_;

    void updateGeometry();
    void updateTextureCoordsAndColor();
    void updateTextureCoordsAndColorForVertex(const BasicVertexArray::iterator v_iterator,
                                              const Rectf32 &cbox, const Rects32 &ctexture_rect);
    void updateColorForVertex(const BasicVertexArray::iterator v_iterator,
                              const Rectf32 &cbox, const Rects32 &ctexture_rect);
    void updateColors();

    vector2df normalizeInBox(const vector2df &position, const Rectf32 box, const Rectf32 &rect) const;
    void update();
};
} // namespace lib::scene

#endif

#pragma once

#ifndef LIB_SCENE_RENDERIZABLE_INCLUDE_HPP
#define LIB_SCENE_RENDERIZABLE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/color.hpp>
#include <lib/scene/hasname.hpp>
#include <lib/scene/vertexarray.hpp>
#include <lib/include/resources/itexture.hpp>

namespace lib::scene
{
class SceneNode;

enum class FigType_t : u8
{
    Quad,
    Shape
};

class Renderizable final : public core::HasName
{
public:
    Renderizable(SceneNode *const parent, str name, const u32 vertexCount);
    ~Renderizable();

    void render();

    PropertyState<FigType_t> figType;
    PropertyState<Rectf32> box;
    PropertyState<Color> color;
    PropertyState<size_type> pointCount;
    PropertyState<function<Color(const BasicVertexArray::const_iterator v_iterator,
        const Rectf32& cbox, const Rects32& ctexture_rect)>> color_modifier;

    BasicProperty<bool> visible{true};

    void setTextureAndTextureRect(sptr<ITexture> texture_,
                                  const Rectf32 &textRect);

    void setTextureFill(sptr<ITexture> texture_);
    Rectf32 normalizedTextureRect() const;

private:
    SceneNode *parent_;

    PropertyState<Rects32> textureRect;
    PropertyState<sptr<ITexture>> texture;

    VertexArray m_vertices;

    void updateGeometry();
    void updateTextureCoordsAndColor();
    void updateTextureCoordsAndColorForVertex(const BasicVertexArray::iterator v_iterator,
        const Rectf32& cbox, const Rects32& ctexture_rect);
    void updateColorForVertex(const BasicVertexArray::iterator v_iterator,
        const Rectf32& cbox, const Rects32& ctexture_rect);
    void updateColors();

    void update();

};
} // namespace lib::scene

#endif

#ifndef HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/array.hpp>

#include <facil_math/include/vector2d.hpp>
#include <facil_math/include/rect.hpp>

namespace haf::backend
{
    class ITexture;
}

namespace haf::ogl
{
class VertexBuffer;
class RenderElement;

class RenderTarget
{
public:
    RenderTarget();

    void clear();
    void setViewPort(fmath::Rects32 const& viewport);
    void setProjection(htps::span<htps::f32 const> const& projection);
    void render(RenderElement const* const render_element);

    htps::str info() const;

private:
    void resetRenderStates();
    void draw(VertexBuffer const& vertexBuffer,
                RenderElement const& render_element);
    void preDraw(RenderElement const& render_element);
    void postDraw(RenderElement const& render_element);
    void applyTexture(backend::ITexture const * const texture);
    void postTexture();
    void bindVertexBuffer(VertexBuffer const* vertexBuffer);

    void drawDebugQuad(RenderElement const* const render_element);
};
}  // namespace haf::backend::sfmlb

#endif

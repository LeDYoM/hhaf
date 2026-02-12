#ifndef HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_REDNERTARGET_INCLUDE_HPP

import htypes;
import facil_math;

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
    void applyTexture(backend::ITexture const* const texture);
    void postTexture();
    void bindVertexBuffer(VertexBuffer const* vertexBuffer);

    void drawDebugQuad(RenderElement const* const render_element);
};
}  // namespace haf::ogl

#endif

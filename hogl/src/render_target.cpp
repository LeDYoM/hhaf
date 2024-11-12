#include <hogl/include/render_target.hpp>
#include <hogl/include/render_element.hpp>
#include <hogl/include/vertex_buffer.hpp>
#include <hogl/include/blend_mode.hpp>
#include "backend_dev/include/ivertex.hpp"
#include "backend_dev/include/itexture.hpp"
#include "opengl/glad.h"
#include "opengl/gl_check.hpp"

using namespace htps;

namespace haf::ogl
{
u32 factorToGlConstant(BlendMode::Factor blendFactor)
{
    switch (blendFactor)
    {
        case ogl::BlendMode::Zero:
            return GL_ZERO;
        case ogl::BlendMode::One:
            return GL_ONE;
        case ogl::BlendMode::SrcColor:
            return GL_SRC_COLOR;
        case ogl::BlendMode::OneMinusSrcColor:
            return GL_ONE_MINUS_SRC_COLOR;
        case ogl::BlendMode::DstColor:
            return GL_DST_COLOR;
        case ogl::BlendMode::OneMinusDstColor:
            return GL_ONE_MINUS_DST_COLOR;
        case ogl::BlendMode::SrcAlpha:
            return GL_SRC_ALPHA;
        case ogl::BlendMode::OneMinusSrcAlpha:
            return GL_ONE_MINUS_SRC_ALPHA;
        case ogl::BlendMode::DstAlpha:
            return GL_DST_ALPHA;
        case ogl::BlendMode::OneMinusDstAlpha:
            return GL_ONE_MINUS_DST_ALPHA;
    }

    assert(false);
    return GL_ZERO;
}

u32 equationToGlConstant(ogl::BlendMode::Equation blendEquation)
{
    switch (blendEquation)
    {
        case ogl::BlendMode::Add:
            return GL_FUNC_ADD;
        case ogl::BlendMode::Subtract:
            return GL_FUNC_SUBTRACT;
        case ogl::BlendMode::ReverseSubtract:
            return GL_FUNC_REVERSE_SUBTRACT;
    }

    assert(false);
    return GL_FUNC_ADD;
}

void applyBlendMode(const BlendMode& mode)
{
    glCheck(glBlendFuncSeparate(factorToGlConstant(mode.colorSrcFactor),
                                factorToGlConstant(mode.colorDstFactor),
                                factorToGlConstant(mode.alphaSrcFactor),
                                factorToGlConstant(mode.alphaDstFactor)));
    glCheck(glBlendEquationSeparate(equationToGlConstant(mode.colorEquation),
                                    equationToGlConstant(mode.alphaEquation)));
}

void RenderTarget::resetRenderStates()
{
    glCheck(glClientActiveTexture(GL_TEXTURE0));
    glCheck(glActiveTexture(GL_TEXTURE0));
    glCheck(glDisable(GL_CULL_FACE));
    glCheck(glDisable(GL_LIGHTING));
    glCheck(glDisable(GL_DEPTH_TEST));
    glCheck(glDisable(GL_ALPHA_TEST));
    glCheck(glEnable(GL_TEXTURE_2D));
    glCheck(glEnable(GL_BLEND));
    glCheck(glMatrixMode(GL_MODELVIEW));
    glCheck(glLoadIdentity());
    glCheck(glEnableClientState(GL_VERTEX_ARRAY));
    glCheck(glEnableClientState(GL_COLOR_ARRAY));
    glCheck(glEnableClientState(GL_TEXTURE_COORD_ARRAY));

    // Apply the default SFML states
    //    render_target.applyBlendMode(sf::BlendAlpha);
    applyTexture(nullptr);
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

    applyBlendMode(ogl::BlendAlpha);
}

RenderTarget::RenderTarget()
{
    gladLoadGL();
    resetRenderStates();
}

void RenderTarget::drawDebugQuad([
    [maybe_unused]] RenderElement const* const render_element)
{
#ifdef DRAW_DEBUG_QUAD
    auto const* const render_element{
        static_cast<SFMLRenderElement const* const>(render_element)};

    using namespace ::sf;
    VertexArray nva(sf::PrimitiveType::LineStrip, 5U);
    auto const bounds{render_element->nativeVertexArray().getBounds()};
    nva[0U] = {{bounds.left, bounds.top}, Color::Green};
    nva[1U] = {{bounds.left + bounds.width, bounds.top}, Color::Green};
    nva[2U] = {{bounds.left + bounds.width, bounds.top + bounds.width},
               Color::Green};
    nva[3U] = {{bounds.left, bounds.top + bounds.width}, Color::Green};
    nva[4U] = {{bounds.left, bounds.top}, sf::Color::Green};
    RenderTarget::draw(nva, render_element->nativeRenderStates().transform);
#endif
}

void RenderTarget::clear()
{
    glCheck(glClearColor(0.0F, 0.0F, 0.0F, 1.0F));
    glCheck(glClear(GL_COLOR_BUFFER_BIT));
}

void applyTransform(const htps::array<htps::f32, 16U>& transform)
{
    glCheck(glLoadMatrixf(transform.cbegin()));
}

void RenderTarget::applyTexture(backend::ITexture const* const texture)
{
    if (texture)
    {
        texture->bind();
    }
    else
    {
        glCheck(glBindTexture(GL_TEXTURE_2D, 0U));
        glCheck(glMatrixMode(GL_TEXTURE));
        glCheck(glLoadIdentity());
        glCheck(glMatrixMode(GL_MODELVIEW));
    }
}

void RenderTarget::postTexture()
{}

void RenderTarget::preDraw(RenderElement const& render_element)
{
    applyTransform(render_element.transformation);
    applyTexture(render_element.texture);
}

void RenderTarget::postDraw(RenderElement const& /*render_element*/)
{
    postTexture();
}

void RenderTarget::bindVertexBuffer(VertexBuffer const* vertexBuffer)
{
    ogl::NativeHandleType handle{0};

    if (vertexBuffer)
    {
        handle = vertexBuffer->getNativeHandle();
    }

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, handle));
}

void RenderTarget::draw(VertexBuffer const& vertexBuffer,
                            RenderElement const& render_element)
{
    size_type firstVertex = 0;

    // Clamp vertexCount to something that makes sense
    size_type vertexCount = vertexBuffer.getVertexCount();

    preDraw(render_element);

    bindVertexBuffer(&vertexBuffer);

    {
        using namespace haf::backend;
        constexpr htps::size_type VertexSize = sizeof(Vertex);
        glCheck(glVertexPointer(Vertex::PositionElements, GL_FLOAT, VertexSize,
                                Vertex::PositionData()));
        glCheck(glColorPointer(Vertex::ColorElements, GL_UNSIGNED_BYTE,
                               VertexSize, Vertex::ColorData()));
        glCheck(glTexCoordPointer(Vertex::TextureRectElements, GL_FLOAT,
                                  VertexSize, Vertex::TextureRectData()));
    }

    // Draw the primitives
    glCheck(glDrawArrays(GL_TRIANGLES, static_cast<GLint>(firstVertex),
                         static_cast<GLsizei>(vertexCount)));

    // Unbind vertex buffer
    bindVertexBuffer(nullptr);

    postDraw(render_element);
}

void RenderTarget::render(RenderElement const* const render_element)
{
    draw(render_element->vertexBuffer(), *render_element);

#ifdef DRAW_DEBUG_QUAD
    drawDebugQuad(tre);
#endif
}

void RenderTarget::setViewPort(fmath::Rects32 const& viewport)
{
    // TODO: Since now we check the view only here, the view is "constant"
    // when the window is resized.

    // Set the viewport
    glCheck(glViewport(viewport.left, viewport.top, viewport.width,
                       viewport.height));
}

void RenderTarget::setProjection(span<f32 const> const& projection)
{
    // Set the projection matrix
    glCheck(glMatrixMode(GL_PROJECTION));
    glCheck(glLoadMatrixf(projection.cbegin()));

    // Go back to model-view mode
    glCheck(glMatrixMode(GL_MODELVIEW));
}

str RenderTarget::info() const
{
    return make_str("name:SFMLwRenderTarget;provider:SFML;provider_version:");/*,
                    SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".",
                    SFML_VERSION_PATCH, ";version:0;subversion:3:patch0");*/
}

}  // namespace haf::backend::sfmlb

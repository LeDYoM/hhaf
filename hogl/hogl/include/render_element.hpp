#ifndef HAF_BACKEND_OGL_RENDER_ELEMENT_INCLUDE_HPP
#define HAF_BACKEND_OGL_RENDER_ELEMENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/array.hpp>
#include <htypes/include/vector.hpp>

#include <backend_dev/include/ivertex.hpp>
#include <hogl/include/vertex_buffer.hpp>

namespace haf::backend
{
class ITexture;
class IShader;
}  // namespace haf::backend

namespace haf::ogl
{
class RenderElement
{
public:
    RenderElement();

    void setSize(htps::size_type const size);
    void setPositions(backend::iPosition const* const positions);
    void setColors(backend::iColor const* const colors);
    void setTexturecoordinates(
        backend::iTextureCoordinates const* const texture_coordinates);
    void setTexture(backend::ITexture const* const texture);
    void setModelViewMatrix(htps::f32 const* const model_view_matrix);
    void setProjectionMatrix(htps::f32 const* const projection_matrix);
    void setShader(backend::IShader const* const shader);

    void updateInternalData() const;

    ogl::VertexBuffer const& vertexBuffer() const noexcept;

    backend::ITexture const* texture{nullptr};
    htps::array<htps::f32, 16U> transformation;
    backend::IShader* shader{nullptr};

private:
    mutable VertexBuffer vertex_buffer_;
    htps::vector<backend::Vertex> vertex_buffer_origin_;
    mutable bool needs_update_;
};
#endif
}
export module hogl:render_element;

import :vertex_buffer;
import htypes;
import backend_dev;

namespace haf::ogl
{
class RenderElement
{
public:
    RenderElement() noexcept :
        vertex_buffer_{VertexBuffer::Usage::Dynamic},
        vertex_buffer_origin_{},
        needs_update_{true}
    {}

    void setSize(htps::size_type const size)
    {
        vertex_buffer_.create(static_cast<std::size_t>(size));
        vertex_buffer_origin_.resize(size);
        needs_update_ = true;
    }

    void setPositions(backend::iPosition const* const positions)
    {
        iPosition const* vtemp{positions};
        for (auto&& vertex_buffer_origin_element : vertex_buffer_origin_)
        {
            vertex_buffer_origin_element.position = *vtemp;
            ++vtemp;
        }
        needs_update_ = true;
    }

    void setColors(backend::iColor const* const colors)
    {
        iColor const* vtemp{colors};
        for (auto&& vertex_buffer_origin_element : vertex_buffer_origin_)
        {
            vertex_buffer_origin_element.color = *vtemp;
            ++vtemp;
        }
        needs_update_ = true;
    }

    void setTexturecoordinates(
        backend::iTextureCoordinates const* const texture_coordinates)
    {
        iTextureCoordinates const* vtemp{texture_coordinates};
        for (auto&& vertex_buffer_origin_element : vertex_buffer_origin_)
        {
            vertex_buffer_origin_element.texture_coordinates = *vtemp;
            ++vtemp;
        }
        needs_update_ = true;
    }

    void setTexture(backend::ITexture const* const texture) noexcept
    {
        texture = p_texture;
    }

    void setModelViewMatrix(htps::f32 const* const model_view_matrix) noexcept
    {
        transformation = htps::span(model_view_matrix, model_view_matrix + 16U);
    }

    void setProjectionMatrix(
        htps::f32 const* const /*projection_matrix*/) noexcept
    {}

    void setShader(backend::IShader const* const shader) noexcept
    {
        shader = const_cast<IShader*>(p_shader);
    }

    void updateInternalData() const
    {
        if (needs_update_)
        {
            vertex_buffer_.update(vertex_buffer_origin_.cbegin());
            needs_update_ = false;
        }
    }

    VertexBuffer const& vertexBuffer() const noexcept;
    {
        return vertex_buffer_;
    }

    backend::ITexture const* texture{nullptr};
    htps::array<htps::f32, 16U> transformation;
    backend::IShader* shader{nullptr};

private:
    mutable VertexBuffer vertex_buffer_;
    htps::vector<backend::Vertex> vertex_buffer_origin_;
    mutable bool needs_update_;
};

}  // namespace haf::ogl
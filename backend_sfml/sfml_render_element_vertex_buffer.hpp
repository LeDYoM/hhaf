#ifndef HAF_BACKEND_SFMLB_RENDER_ELEMENT_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_RENDER_ELEMENT_INCLUDE_HPP

#include <backend_dev/include/irender_element.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#ifdef USE_VERTEX_ARRAY
#include <SFML/Graphics/VertexArray.hpp>
namespace haf::backend::sfmlb
{
class SFMLRenderElementVertexBuffer : public IRenderElement
{
public:
    ~SFMLRenderElementVertexBuffer() override;

    void setSize(htps::size_type const size) override;
    void setPositions(iPosition const* const positions) override;
    void setColors(iColor const* const colors) override;
    void setTexturecoordinates(
        iTextureCoordinates const* const texture_coordinates) override;
    void setTexture(ITexture const* const texture) override;
    void setModelViewMatrix(htps::f32 const* const model_view_matrix) override;
    void setProjectionMatrix(htps::f32 const* const projection_matrix) override;
    void setShader(IShader const* const shader) override;

    void render(sf::RenderTarget& target) const;

private:
    sf::VertexArray vertex_array_{sf::PrimitiveType::Triangles};
    mutable sf::RenderStates render_states_ = sf::RenderStates::Default;
};
}  // namespace haf::backend::sfmlb

#else
#include <SFML/Graphics/VertexBuffer.hpp>

namespace haf::backend::sfmlb
{
class SFMLRenderElementVertexBuffer : public IRenderElement
{
public:
    ~SFMLRenderElementVertexBuffer() override;

    void setSize(htps::size_type const size) override;
    void setPositions(iPosition const* const positions) override;
    void setColors(iColor const* const colors) override;
    void setTexturecoordinates(
        iTextureCoordinates const* const texture_coordinates) override;
    void setTexture(ITexture const* const texture) override;
    void setModelViewMatrix(htps::f32 const* const model_view_matrix) override;
    void setProjectionMatrix(htps::f32 const* const projection_matrix) override;
    void setShader(IShader const* const shader) override;

    void render(sf::RenderTarget& target) const;

private:
    mutable sf::VertexBuffer vertex_buffer_{sf::PrimitiveType::Triangles, sf::VertexBuffer::Usage::Static};
    htps::vector<sf::Vertex> vertex_buffer_origin_;
    mutable bool needs_update_{true};
    mutable sf::RenderStates render_states_ = sf::RenderStates::Default;
};
#endif
}  // namespace haf::backend::sfmlb

#endif

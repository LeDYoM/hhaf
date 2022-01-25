#ifndef HAF_BACKEND_SFMLB_RENDER_ELEMENT_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_RENDER_ELEMENT_INCLUDE_HPP

#include <backend_dev/include/irender_element.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace haf::backend::sfmlb
{
class RenderElement : public IRenderElement
{
public:
    void setSize(htps::size_type const size) override;
    void setVertexData(iVertex const* const vertex_data) override;
    void setTexture(ITexture const* const texture) override;
    void setModelViewMatrix(htps::f32 const* const model_view_matrix) override;
    void setProjectionMatrix(htps::f32 const* const projection_matrix) override;
    void setTexture(ITexture const* const texture) override;

private:
    sf::VertexArray vertex_array_;
};
}  // namespace haf::backend::sfmlb

#endif

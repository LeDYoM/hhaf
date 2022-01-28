#ifndef HAF_BACKEND_SFMLB_RENDER_ELEMENT_INCLUDE_HPP
#define HAF_BACKEND_SFMLB_RENDER_ELEMENT_INCLUDE_HPP

#include <backend_dev/include/irender_element.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace haf::backend::sfmlb
{
class RenderElement : public IRenderElement
{
public:
    void setPrimitiveType(iPrimitiveType const primitive_type) override;
    void setSize(htps::size_type const size) override;
    void setVertexData(iVertex const* const vertex_data) override;
    void setTexture(ITexture const* const texture) override;
    void setModelViewMatrix(htps::f32 const* const model_view_matrix) override;
    void setProjectionMatrix(htps::f32 const* const projection_matrix) override;
    void setShader(IShader const* const shader) override;
    ~RenderElement() override;

    constexpr sf::VertexArray const& nativeVertexArray() const noexcept
    {
        return vertex_array_;
    }
    constexpr sf::RenderStates const& nativeRenderStates() const noexcept
    {
        return render_states_;
    }

private:
    sf::VertexArray vertex_array_;
    sf::RenderStates render_states_ = sf::RenderStates::Default;
};
}  // namespace haf::backend::sfmlb

#endif

#ifndef HAF_COMPONENT_RENDERIZABLES_INCLUDE_HPP
#define HAF_COMPONENT_RENDERIZABLES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/vector.hpp>

#include <haf/include/render/renderizable.hpp>
#include <haf/include/render/renderizable_builder.hpp>

namespace haf::scene
{
class SceneNode;

class Renderizables
{
public:
    /**
     * @brief Construct a new Renderizables object with a parent node
     * @param scene_node Node to be used as a parent
     */
    explicit Renderizables(htps::rptr<SceneNode> scene_node) noexcept;

    /**
     * @brief Create a Renderizable object
     *
     * @param name The name of the Renderizable node.
     * @param figure_type Type of the figure to generate.
     * @param box Box containing the Renderizable.
     * @param color Color of the Renderizable.
     * @param texture Pointer to the texture to use
     * @param shader Pointer to the Shader to use
     * @param num_points Number of points of the Renderizable.
     * @return htps::sptr<Renderizable>
     */
    htps::sptr<render::Renderizable> createRenderizable(
        htps::str name,
        render::FigType_t figure_type,
        htps::Rectf32 box,
        Color color,
        htps::sptr<res::ITexture> texture,
        htps::sptr<res::IShader> shader,
        htps::size_type num_points);

    render::RenderizableBuilder renderizableBuilder();

    void removeRenderizable(const htps::sptr<render::Renderizable>& element);
    void clearRenderizables();

    template <typename T>
    constexpr void for_each_node_as(
        htps::function<void(const htps::sptr<T>&)> action)
    {
        for_each_node([&action](const htps::sptr<render::Renderizable>& node) {
            if (auto tnode = std::dynamic_pointer_cast<T>(node))
            {
                action(tnode);
            }
        });
    }

    void for_each_node(
        htps::function<void(const htps::sptr<render::Renderizable>&)> action) const;

    void updateRenderizables();

private:
    void addRenderizable(htps::sptr<render::Renderizable> newElement);
    htps::rptr<SceneNode> scene_node_;
    htps::vector<htps::sptr<render::Renderizable>> render_nodes_;
};
}  // namespace haf::scene

#endif

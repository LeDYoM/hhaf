#ifndef HAF_COMPONENT_RENDERIZABLES_INCLUDE_HPP
#define HAF_COMPONENT_RENDERIZABLES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/vector.hpp>

#include <haf/include/render/renderizable.hpp>
#include <haf/include/render/renderizable_builder.hpp>

namespace haf::scene
{
class TransformableSceneNode;
}

namespace haf::render
{
class Renderizables
{
public:
    /**
     * @brief Construct a new Renderizables object with a parent node
     * @param scene_node Node to be used as a parent
     */
    explicit Renderizables(
        htps::rptr<scene::TransformableSceneNode> scene_node) noexcept;

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
    htps::sptr<Renderizable> createRenderizable(
        RenderizableBuilderData&& renderizable_data);

    RenderizableBuilder renderizableBuilder();

    void removeRenderizable(const htps::sptr<Renderizable>& element);
    void clearRenderizables();

    template <typename T>
    constexpr void for_each_node_as(
        htps::function<void(htps::sptr<T> const&)> action)
    {
        for_each_node([&action](const htps::sptr<Renderizable>& node) {
            if (auto tnode = std::dynamic_pointer_cast<T>(node))
            {
                action(tnode);
            }
        });
    }

    void for_each_node(
        htps::function<void(htps::sptr<Renderizable> const&)> action) const;

    void updateRenderizables();

private:
    void addRenderizable(htps::sptr<Renderizable> newElement);
    htps::rptr<scene::TransformableSceneNode> scene_node_;
    htps::vector<htps::sptr<Renderizable>> render_nodes_;
};
}  // namespace haf::render

#endif

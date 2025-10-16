HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDERIZABLES_INCLUDE_HPP
#define HAF_RENDER_RENDERIZABLES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/render/renderizable_builder.hpp>

namespace haf::render
{
class Renderizables
{
public:
    /**
     * @brief Construct a new Renderizables object with a parent node
     */
    Renderizables() noexcept = default;

    void setSceneNode(htps::rptr<scene::SceneNode> scene_node) noexcept;

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

    void removeRenderizable(htps::sptr<Renderizable> const& element);
    void clearRenderizables();

    template <typename T>
    constexpr void for_each_node_as(
        htps::function<void(htps::sptr<T> const&)> action) const
    {
        for_each_node([&action](htps::sptr<Renderizable> const& node) {
            if (auto const tnode{htps::dynamic_pointer_cast<T>(node)})
            {
                action(tnode);
            }
        });
    }

    void for_each_node(
        htps::function<void(htps::sptr<Renderizable> const&)> action) const;

    void updateRenderizables(bool const parent_transformation_changed);

    htps::sptr<Renderizable> const& operator[](
        htps::size_type const index) const noexcept;

    htps::size_type size() const;
    bool empty() const noexcept;

    htps::rptr<scene::SceneNode const> sceneNode() const noexcept;

private:
    void addRenderizable(htps::sptr<Renderizable> newElement);

    htps::rptr<scene::SceneNode> m_scene_node;
    htps::vector<htps::sptr<Renderizable>> m_render_nodes;
};
}  // namespace haf::render

#endif

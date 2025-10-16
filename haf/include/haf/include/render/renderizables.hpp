HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RENDERIZABLES_INCLUDE_HPP
#define HAF_RENDER_RENDERIZABLES_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/render/renderizable_builder.hpp>

namespace haf::render
{

class Renderizables
{
public:
    void setSceneNode(htps::rptr<scene::SceneNode> scene_node) noexcept;

    /**
     * @brief Create a Renderizables object
     * @param renderizable_data A RenderizableData value to own in this class
     */
    core::sptr<Renderizable> createRenderizable(
        RenderizableBuilderData&& renderizable_data);

    RenderizableBuilder renderizableBuilder();

    void removeRenderizable(htps::sptr<Renderizable> const& element);
    void clearRenderizables();

    template <typename T>
    constexpr void for_each_node_as(
        core::function<void(htps::sptr<T> const&)> action) const
    {
        for_each_node([&action](htps::sptr<Renderizable> const& node) {
            if (auto const tnode{htps::dynamic_pointer_cast<T>(node)})
            {
                action(tnode);
            }
        });
    }

    void for_each_node(
        core::function<void(core::sptr<Renderizable> const&)> action) const;

    void updateRenderizables(bool const parent_transformation_changed);

    core::sptr<Renderizable> const& operator[](
        core::size_type const index) const noexcept;

    core::size_type size() const;
    bool empty() const noexcept;

    core::rptr<scene::SceneNode const> sceneNode() const noexcept;

private:
    void addRenderizable(htps::sptr<Renderizable> newElement);

    core::rptr<scene::SceneNode> m_scene_node;
    core::vector<core::sptr<Renderizable>> m_render_nodes;
};
}  // namespace haf::render

#endif

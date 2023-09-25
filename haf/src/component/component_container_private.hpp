HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_COMPONENT_CONTAINER_PRIVATE_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_CONTAINER_PRIVATE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene_update_time.hpp>

namespace haf::scene
{
    class SceneManager;
}

namespace haf::component
{
struct ComponentContainer::ComponentContainerPrivate
{
    core::sptr<Component> getExistingComponent(core::str_view typeName) const;

    core::rptr<scene::SceneNode> const attachable_;
    scene::SceneManager& m_scene_manager;
    core::vector<core::sptr<Component>> components_;

    ComponentContainerPrivate(core::rptr<scene::SceneNode> attachable) noexcept;
    void updateComponents(scene::SceneUpdateTime const sceneUpdateTime);
    void clearComponents();
};

}  // namespace haf::component

#endif
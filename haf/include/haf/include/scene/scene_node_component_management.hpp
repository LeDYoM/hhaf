HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_NODE_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_SCENE_NODE_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/events/connection.hpp>

namespace haf::component
{
class Component;
}
namespace haf::scene
{
class SceneNode;

class HAF_API SceneNodeComponentManagerment
{
public:
    explicit SceneNodeComponentManagerment(
        core::sptr<SceneNode> scene_node) noexcept;

    explicit SceneNodeComponentManagerment(
        core::rptr<SceneNode> scene_node) noexcept;

    explicit SceneNodeComponentManagerment(SceneNode& scene_node) noexcept;

    core::pair<core::sptr<SceneNode>, core::sptr<component::Component>>
    createSceneNodeWithComponent(core::str_view name,
                                 core::str_view componentName);

    template <typename T>
    core::pair<core::sptr<SceneNode>, core::sptr<T>>
    createSceneNodeWithComponent(core::str_view name)
    {
        auto result{
            createSceneNodeWithComponent(core::move(name), T::StaticTypeName)};
        return {result.first, core::static_pointer_cast<T>(result.second)};
    }

private:
    SceneNode& m_scene_node;
};

}  // namespace haf::scene

#endif

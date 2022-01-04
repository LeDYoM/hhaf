#ifndef HAF_COMPONENT_COMPONENT_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/component/icomponent_attached_node.hpp>
#include <haf/include/component/icomponent.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scenenode_cast.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::component
{
template <typename T>
class ComponentForType : public IComponent, public IComponentAttachedNode<T>
{
    using ComponentAttachedNode = IComponentAttachedNode<T>;

public:
    /**
     * @brief Interface to be implemented to update the component
     */
    void update() override {}

    /**
     * @brief Destroy the Attachable object
     */
    virtual ~ComponentForType() = default;

    /**
     * @brief Method called after the component is attached to a node.
     * Override it to perform initialization
     */
    virtual void onAttached() override {}

    void setAttachedNode(
        htps::rptr<scene::SceneNode> const attachedNode) noexcept override
    {
        auto converted{
            scene::sceneNodeCast<ComponentAttachedNode::type>(attachedNode)};
        ComponentAttachedNode::setAttachedNodeNode(converted);
        onAttached();
    }
};

using Component = ComponentForType<scene::SceneNode>;

}  // namespace haf::component

#endif

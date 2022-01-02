#ifndef HAF_COMPONENT_COMPONENT_INCLUDE_HPP
#define HAF_COMPONENT_COMPONENT_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/component/icomponent_attached_node.hpp>
#include <haf/include/component/icomponent.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::component
{

class Component : public IComponent, public IComponentAttachedNode
{
public:
    /**
     * @brief Interface to be implemented to update the component
     */
    void update() override {}

    /**
     * @brief Destroy the Attachable object
     */
    virtual ~Component() = default;

    /**
     * @brief Method called after the component is attached to a node.
     * Override it to perform initialization
     */
    virtual void onAttached() override {}

    void setAttachedNode(htps::rptr<scene::SceneNode> attachedNode) noexcept
    {
        IComponentAttachedNode::setAttachedNodeNode(attachedNode);
        onAttached();
    }
};

}  // namespace haf::component

#endif

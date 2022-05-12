HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_ICOMPONENT_INCLUDE_HPP
#define HAF_COMPONENT_ICOMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/component/icomponent_attached_node.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::component
{

class IComponent
{
public:
    /**
     * @brief Interface to be implemented to update the component
     */
    virtual void update() = 0;

    /**
     * @brief Destroy the Attachable object
     */
    virtual ~IComponent() = default;

    /**
     * @brief Method called after the component is attached to a node.
     * Override it to perform initialization
     */
    virtual void onAttached() = 0;

    virtual void setAttachedNode(
        htps::rptr<scene::SceneNode> const attachedNode) noexcept = 0;
};

}  // namespace haf::component

#endif

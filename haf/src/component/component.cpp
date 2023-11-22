#include <haf/include/component/component.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::component
{
Component::Component()  = default;
Component::~Component() = default;

bool Component::addRequirements(ComponentRequirements&)
{
    return true;
}

void Component::setAttachedNode(pointer const attachedNode)
{
    attachedNode_ = attachedNode;
    onAttached();
}

void Component::onAttached()
{}

Component::const_pointer Component::attachedNode() const noexcept
{
    return attachedNode_;
}

Component::pointer Component::attachedNode() noexcept
{
    return attachedNode_;
}

}  // namespace haf::component

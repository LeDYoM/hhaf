#include <htypes/include/types.hpp>
#include <haf/include/scene/componentcontainer.hpp>

namespace haf::scene
{

ComponentContainer::ComponentContainer(htps::rptr<AttachableType> init) :
    component_container_{init}, static_component_container_{init}
{}

void ComponentContainer::updateComponents()
{
    component_container_.updateComponents();
    static_component_container_.updateComponents();
}

void ComponentContainer::clearComponents()
{
    component_container_.clearComponents();
    static_component_container_.clearComponents();
}

}  // namespace haf::scene

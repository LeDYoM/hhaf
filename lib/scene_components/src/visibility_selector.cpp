#include "visibility_selector.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib::scene
{

void VisibilitySelectorComponent::configure(mtps::size_type first_index)
{
    hideAll();
    show(active_index, true);
}

void VisibilitySelectorComponent::show(mtps::size_type index, bool force)
{
    if (index != active_index || force)
    {
        attachedNode()->sceneNodes()[active_index]->visible = false;
        active_index = index;
        attachedNode()->sceneNodes()[active_index]->visible = true;
    }
}

void VisibilitySelectorComponent::hideAll()
{
    for (auto &scene_node : attachedNode()->sceneNodes())
    {
        scene_node->visible = false;
    }
}

void VisibilitySelector::configure(mtps::size_type first_index)
{
    componentOfType<VisibilitySelectorComponent>()->configure(first_index);
}

void VisibilitySelector::show(mtps::size_type index, bool force)
{
    componentOfType<VisibilitySelectorComponent>()->show(index, force);
}

} // namespace lib::scene::nodes

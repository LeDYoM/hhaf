#include "visibility_selector.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib::scene
{

void VisibilitySelector::configure(size_type first_index)
{
    hideAll();
    show(active_index, true);
}

void VisibilitySelector::show(size_type index, bool force)
{
    if (index != active_index || force)
    {
        attachedNode()->sceneNodes()[active_index]->visible = false;
        active_index = index;
        attachedNode()->sceneNodes()[active_index]->visible = true;
    }
}

void VisibilitySelector::hideAll()
{
    for (auto &scene_node : attachedNode()->sceneNodes())
    {
        scene_node->visible = false;
    }
}

void VisibilitySelector::onAttached()
{

}

} // namespace lib::scene::nodes

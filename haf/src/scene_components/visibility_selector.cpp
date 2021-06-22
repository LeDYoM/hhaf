#include <haf/include/scene_components/visibility_selector.hpp>
#include <haf/include/scene/componentcontainer.hpp>

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

using namespace htps;

namespace haf::scene
{
void VisibilitySelectorComponent::configure(size_type first_index)
{
    hideAll();
    show(first_index, true);
}

void VisibilitySelectorComponent::show(size_type index, bool force)
{
    if (index != active_index || force)
    {
        attachedNode()->sceneNodes()[active_index]->prop<Visible>().set(false);
        active_index = index;
        attachedNode()->sceneNodes()[active_index]->prop<Visible>().set(true);
    }
}

void VisibilitySelectorComponent::hideAll()
{
    for (auto& scene_node : attachedNode()->sceneNodes())
    {
        scene_node->prop<Visible>().set(false);
    }
}

void VisibilitySelector::configure(size_type first_index)
{
    components().componentOfType<VisibilitySelectorComponent>()->configure(first_index);
}

void VisibilitySelector::show(size_type index, bool force)
{
    components().componentOfType<VisibilitySelectorComponent>()->show(index, force);
}

}  // namespace haf::scene

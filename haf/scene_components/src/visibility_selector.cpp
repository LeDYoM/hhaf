#include "visibility_selector.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

using namespace mtps;

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
        attachedNode()
            ->sceneNodes()[active_index]
            ->sceneNodeProperties()
            .set<Visible>(false);
        active_index = index;
        attachedNode()
            ->sceneNodes()[active_index]
            ->sceneNodeProperties()
            .set<Visible>(true);
    }
}

void VisibilitySelectorComponent::hideAll()
{
    for (auto& scene_node : attachedNode()->sceneNodes())
    {
        scene_node->sceneNodeProperties().set<Visible>(false);
    }
}

void VisibilitySelector::configure(size_type first_index)
{
    componentOfType<VisibilitySelectorComponent>()->configure(first_index);
}

void VisibilitySelector::show(size_type index, bool force)
{
    componentOfType<VisibilitySelectorComponent>()->show(index, force);
}

}  // namespace haf::scene

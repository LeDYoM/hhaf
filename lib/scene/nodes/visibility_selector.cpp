#include "visibility_selector.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib::scene::nodes
{
VisibilitySelector::VisibilitySelector(SceneNode *parent, str name)
    : BaseClass{parent, std::move(name)} {}

VisibilitySelector::~VisibilitySelector() = default;

void VisibilitySelector::configure(size_type first_index)
{
    hideAll();
    show(active_index, true);
}

void VisibilitySelector::show(size_type index, bool force)
{
    if (index != active_index || force)
    {
        sceneNodes()[active_index]->visible = false;
        active_index = index;
        sceneNodes()[active_index]->visible = true;
    }
}

void VisibilitySelector::hideAll()
{
    for (auto &scene_node : sceneNodes())
    {
        scene_node->visible = false;
    }
}

} // namespace lib::scene::nodes

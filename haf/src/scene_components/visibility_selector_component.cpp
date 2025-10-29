#include <haf/include/scene_components/visibility_selector_component.hpp>
#include <haf/include/scene/scene_node.hpp>

#include <htypes/include/types.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::scene
{
VisibilitySelectorComponent::VisibilitySelectorComponent() : visible_index{0U}
{}

void VisibilitySelectorComponent::update()
{
    if (visible_index.readResetHasChanged())
    {
        attachedNode()->set_property_for_each_node(&SceneNode::Enabled, false);

        LogAsserter::log_assert(
            visible_index() < attachedNode()->sceneNodes().size(),
            "Invalid visible_index");

        if (visible_index() < attachedNode()->sceneNodes().size())
        {
            attachedNode()->sceneNodes()[visible_index()]->Enabled = true;
        }
    }
}

}  // namespace haf::scene

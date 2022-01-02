#include <haf/include/scene_components/visibility_selector_component.hpp>
#include <haf/include/scene/scene_node.hpp>

#include <htypes/include/types.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::scene
{
VisibilitySelectorComponent::VisibilitySelectorComponent() :
    Component{}, visible_index{0U}
{}

void VisibilitySelectorComponent::update()
{
    if (visible_index.readResetHasChanged())
    {
        attachedNode()->set_property_for_each_sceneNode<Visible>(false);

        LogAsserter::log_assert(
            visible_index() < attachedNode()->sceneNodes().size(),
            "Invalid visible_index");

        if (visible_index() < attachedNode()->sceneNodes().size())
        {
            attachedNode()->sceneNodes()[visible_index()]->prop<Visible>().set(
                true);
        }
    }
}

}  // namespace haf::scene

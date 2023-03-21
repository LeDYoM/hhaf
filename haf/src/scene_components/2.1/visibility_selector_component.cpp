#include <haf/include/scene_components/2.1/visibility_selector_component.hpp>
#include <haf/include/scene/scene_node.hpp>

#include <htypes/include/types.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::scene
{
VisibilitySelectorComponent::VisibilitySelectorComponent() noexcept :
    visible_index{0U}
{}

void VisibilitySelectorComponent::onUpdateVisibleIndex()
{
    auto sceneNodesComponent{getComponent<SceneNodesComponent>()};

    sceneNodesComponent->forEach(
        [](const auto node) { node->Visible = false; });
    if (auto sceneNode{sceneNodesComponent->getByIndex(visible_index())};
        sceneNode != nullptr)
    {
        sceneNode->Visible = true;
    }
    else
    {
        DisplayLog::warn("visible_index out of range");
    }
}

void VisibilitySelectorComponent::onAttached()
{
    m_receiver
        .connect(getComponent<SceneNodesComponent>()->onNodeAdded,
                 {this, &VisibilitySelectorComponent::onNodeAdded})
        .connect(getComponent<SceneNodesComponent>()->onNodeRemoved,
                 {this, &VisibilitySelectorComponent::onNodeRemoved});

    addUpdater({this, &VisibilitySelectorComponent::onUpdateVisibleIndex},
               &visible_index);
}

void VisibilitySelectorComponent::onNodeAdded(SceneNodeSPtr const&)
{
    visible_index.setChanged();
}

void VisibilitySelectorComponent::onNodeRemoved(SceneNodeSPtr const&)
{
    visible_index.setChanged();
}

}  // namespace haf::scene

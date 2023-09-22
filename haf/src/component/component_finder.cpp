#include <haf/include/component/component_finder.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scenenodeparent.hpp>

using namespace haf::core;
using namespace haf::scene;

namespace haf::component
{
ComponentFinder::ComponentFinder(rptr<SceneNode> node) noexcept : m_node{node}
{}

sptr<Component> ComponentFinder::findParentComponent(str_view name) const
{
    // Connect to receive the updates from a parent global transformation
    if (auto parentNode{m_node->parent()}; parentNode != nullptr)
    {
        return parentNode->componentContainer().getExistingComponent(name);
    }
    return {};
}

sptr<Component> ComponentFinder::findAncestorComponent(str_view name) const
{
    // Connect to receive the updates from a parent global transformation
    for (auto parentNode{m_node->parent()}; parentNode != nullptr;
         parentNode = parentNode->parent())
    {
        auto result{parentNode->componentContainer().getExistingComponent(name)};
        if (result)
        {
            return result;
        }
    }
    return {};
}

}  // namespace haf::component

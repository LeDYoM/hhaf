#include <haf/scene/include/scenenode.hpp>
#include <haf/scene/include/scenenode_utils.hpp>

using namespace htps;

namespace haf::scene
{
void for_each_sceneNode(
    SceneNodes& node,
    htps::function<void(htps::sptr<SceneNode> const&)> action)
{
    std::for_each(node.sceneNodes().cbegin(), node.sceneNodes().cend(), action);
}

void for_each_sceneNode(
    SceneNodes const& node,
    htps::function<void(htps::sptr<SceneNode const> const&)> action)
{
    std::for_each(node.sceneNodes().cbegin(), node.sceneNodes().cend(), action);
}

}  // namespace haf::scene

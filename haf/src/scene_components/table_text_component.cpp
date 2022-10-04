#include <haf/include/scene_components/table_text_component.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

using namespace htps;

namespace haf::scene
{
sptr<nodes::SceneNodeText> TextTableNode::text(vector2dst const& index)
{
    return nodeAt(index);
}
}  // namespace haf::scene

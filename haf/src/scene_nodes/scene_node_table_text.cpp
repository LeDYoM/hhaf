#include <haf/include/scene_nodes/scene_node_table_text.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

using namespace htps;
using namespace fmath;

namespace haf::scene::nodes
{
sptr<SceneNodeText> TextTableNode::text(vector2dst const& index)
{
    return nodeAt(index);
}
}  // namespace haf::scene::nodes

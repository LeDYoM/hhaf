#ifndef HAF_SCENE_NODE_TABLE_TEXT_INCLUDE_HPP
#define HAF_SCENE_NODE_TABLE_TEXT_INCLUDE_HPP

#include <haf/include/scene_nodes/scene_node_table.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

namespace haf::scene::nodes
{
class TextTableNode : public TableNode<SceneNodeText>
{
    using BaseClass = TableNode<SceneNodeText>;

public:
    using BaseClass::BaseClass;
    using BaseClass::prop;
};
}  // namespace haf::scene::nodes

#endif

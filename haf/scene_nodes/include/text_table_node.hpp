#ifndef HAF_SCENE_TEXT_TABLENODE_INCLUDE_HPP
#define HAF_SCENE_TEXT_TABLENODE_INCLUDE_HPP

#include <haf/scene_nodes/include/tablenode.hpp>
#include <haf/scene_nodes/include/scenenodetext.hpp>

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

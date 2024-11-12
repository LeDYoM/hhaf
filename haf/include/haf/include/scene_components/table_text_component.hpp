HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_TABLE_TEXT_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_TABLE_TEXT_COMPONENT_INCLUDE_HPP

#include <haf/include/scene_components/table_component.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

namespace haf::scene
{
class TextTableNode : public TableNode<nodes::SceneNodeText>
{
    using BaseClass = TableNode<nodes::SceneNodeText>;

public:
    using BaseClass::BaseClass;

    htps::sptr<nodes::SceneNodeText> text(fmath::vector2dst const& index);
};
}  // namespace haf::scene::nodes

#endif

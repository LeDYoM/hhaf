HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_NODE_TEXT_QUAD_INCLUDE_HPP
#define HAF_SCENE_NODE_TEXT_QUAD_INCLUDE_HPP

#include <haf/include/scene_nodes/scene_node_table.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/scene_nodes/scene_node_table_text.hpp>

namespace haf::scene::nodes
{
class TextQuad : public TextTableNode
{
    using BaseClass = TextTableNode;

public:
    using BaseClass::BaseClass;

    void onCreated() override;

    void onElementCreated(htps::vector2dst, htps::sptr<SceneNodeText> const&);

};
}  // namespace haf::scene::nodes

#endif

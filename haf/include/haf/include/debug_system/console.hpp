HTPS_PRAGMA_ONCE
#ifndef HAF_CONSOLE_INCLUDE_HPP
#define HAF_CONSOLE_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <haf/include/scene_nodes/scene_node_table_text.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

namespace haf
{
class Console : public haf::scene::nodes::TextTableNode
{
    using BaseClass = haf::scene::nodes::TextTableNode;

public:
    using BaseClass::BaseClass;
    void onCreated() override;

    void tableNodeCreated(
        htps::vector2dst,
        htps::sptr<haf::scene::nodes::SceneNodeText> const&) override;
    void onAllTableElementsCreated(htps::vector2dst const table_size) override;

    void setText(htps::str const& text);
};
}  // namespace haf

#endif
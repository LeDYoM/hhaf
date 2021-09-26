#ifndef HAF_CONSOLE_INCLUDE_HPP
#define HAF_CONSOLE_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/scene_nodes/text_table_node.hpp>

namespace haf
{
class Console : public haf::scene::nodes::TextTableNode
{
    using BaseClass = haf::scene::nodes::TextTableNode;

public:
    using BaseClass::BaseClass;
    void onCreated() override;
};
}  // namespace haf

#endif
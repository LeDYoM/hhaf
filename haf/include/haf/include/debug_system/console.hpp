HTPS_PRAGMA_ONCE
#ifndef HAF_CONSOLE_INCLUDE_HPP
#define HAF_CONSOLE_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <haf/include/scene_components/table_text_component.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_requirements.hpp>

namespace haf
{
class Console : public component::Component
{
    using BaseClass = component::Component;

public:
    using BaseClass::BaseClass;
    void onAttached() override;

    void tableNodeCreated(
        htps::vector2dst const&,
        htps::sptr<haf::scene::nodes::SceneNodeText> const&);

    void setText(htps::vector2dst const& nodeIndex, htps::str const& text);
private:
    void addRequirements(component::ComponentRequirements&) override;
    htps::sptr<scene::TextTableNode> m_textTableNode;
};
}  // namespace haf

#endif
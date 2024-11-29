HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP
#define HAF_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/component/component.hpp>

namespace haf::scene
{
class DiscreteTextComponent final
    : public component::Component  // ComponentForType<nodes::SceneNodeText>
{
    using BaseClass = component::Component;

public:
    prop::BasicProperty<bool> circleAroud{true};
    prop::BasicProperty<htps::string_vector> data;
    void incrementIndex() noexcept;
    void decrementIndex() noexcept;
    prop::PropertyState<htps::size_type> index{0U};

    virtual void update() override;

private:
    void _setText(htps::str const& nText);
};
}  // namespace haf::scene

#endif

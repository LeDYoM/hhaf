HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP
#define HAF_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/component/icomponent.hpp>

namespace haf::scene
{
class DiscreteTextComponent final
    : public component::IComponent //ComponentForType<nodes::SceneNodeText>
{
    using BaseClass = component::IComponent;

public:
    htps::BasicProperty<bool> circleAroud{true};
    htps::BasicProperty<htps::string_vector> data;
    void incrementIndex() noexcept;
    void decrementIndex() noexcept;
    htps::PropertyState<htps::size_type> index{0U};

    virtual void update() override;

private:
    void _setText(htps::str const& nText);
};
}  // namespace haf::scene

#endif

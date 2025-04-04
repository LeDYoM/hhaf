HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP
#define HAF_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/properties/basic_property.hpp>
#include <haf/include/properties/property_state.hpp>
#include <haf/include/component/component.hpp>

namespace haf::scene
{
class DiscreteTextComponent final : public component::Component
{
    using BaseClass = component::Component;

public:
    void incrementIndex() noexcept;
    void decrementIndex() noexcept;

    prop::PropertyState<htps::size_type> index{0U};
    prop::BasicProperty<bool> circleAroud{true};
    prop::BasicProperty<htps::string_vector> data;

    virtual void update() override;

private:
    void _setText(htps::str const& nText);
};
}  // namespace haf::scene

#endif

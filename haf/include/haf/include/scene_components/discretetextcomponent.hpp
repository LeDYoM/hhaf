#ifndef HAF_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP
#define HAF_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene_nodes/scenenodetext.hpp>
#include <haf/include/scene/icomponent.hpp>

namespace haf::scene
{
class DiscreteTextComponent final : public IComponent
{
public:
    using BaseClass = IComponent;

    htps::BasicProperty<bool> circleAroud{true};
    htps::BasicProperty<htps::string_vector> data;
    void incrementIndex() noexcept;
    void decrementIndex() noexcept;
    htps::PropertyState<htps::size_type> index{0U};

    virtual void update() override;

private:
    void _setText(const htps::str& nText);
};
}  // namespace haf::scene

#endif

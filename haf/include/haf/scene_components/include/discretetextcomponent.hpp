#ifndef HAF_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP
#define HAF_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/scene_nodes/include/scenenodetext.hpp>
#include <haf/scene/include/icomponent.hpp>

namespace haf::scene
{
class DiscreteTextComponent final : public IComponent
{
public:
    using BaseClass = IComponent;

    mtps::BasicProperty<bool> circleAroud{true};
    mtps::BasicProperty<mtps::string_vector> data;
    void incrementIndex() noexcept;
    void decrementIndex() noexcept;
    mtps::PropertyState<mtps::size_type> index{0U};

    virtual void update() override;

private:
    void _setText(const mtps::str& nText);
};
}  // namespace haf::scene

#endif

#pragma once

#ifndef LIB_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP
#define LIB_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene_nodes/include/scenenodetext.hpp>
#include <lib/scene/include/icomponent.hpp>

namespace lib::scene
{
class DiscreteTextComponent : public IComponent
{
public:
    using BaseClass = IComponent;
    DiscreteTextComponent() {}
    virtual ~DiscreteTextComponent() {}

    BasicProperty<bool> circleAroud{true};
    BasicProperty<string_vector> data;
    void incrementIndex() noexcept;
    void decrementIndex() noexcept;
    PropertyState<size_type> index{0};

    virtual void update() override final;

private:
    void _setText(const str &nText);
};
} // namespace lib::scene

#endif

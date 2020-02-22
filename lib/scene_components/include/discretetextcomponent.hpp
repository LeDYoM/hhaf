#pragma once

#ifndef LIB_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP__
#define LIB_COMPONENT_DISCRETE_TEXT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/nodes/scenenodetext.hpp>
#include <lib/scene/icomponent.hpp>

namespace lib::scene
{
    class DiscreteTextComponent : public IComponent
    {
    public:
        using BaseClass = IComponent;
        DiscreteTextComponent() {}
        virtual ~DiscreteTextComponent() {}

        BasicProperty<bool> circleAroud{ true };
        BasicProperty<string_vector> data;
        void incrementIndex() noexcept;
        void decrementIndex() noexcept;
        PropertyState<size_type> index{ 0 };

        virtual void update() override final;
    private:
        void _setText(const str&nText);
    };
}

#endif

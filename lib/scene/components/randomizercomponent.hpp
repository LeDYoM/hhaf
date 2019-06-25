#pragma once

#ifndef LIB_COMPONENT_RANDOMIZER_COMPONENT_INCLUDE_HPP
#define LIB_COMPONENT_RANDOMIZER_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>

#include <lib/include/properties.hpp>
#include <lib/scene/components/icomponent.hpp>

namespace lib::scene
{
    /**
    * This component class is intended to be used to generate
    * a series of random numbers.
    */
    class RandomizerComponent final : public IComponent
    {
    public:
        RandomizerComponent();
        ~RandomizerComponent() override;
        u32 getUInt(const size_type max, const size_type min = 0U) const;

        PropertyTrigger<size_type> channel;

        void onAttached() override;
    private:
        class RandomizerPrivate;
        uptr<RandomizerPrivate> priv_;
	};
}

#endif

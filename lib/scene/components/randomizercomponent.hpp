#pragma once

#ifndef LIB_COMPONENT_RANDOMIZER_COMPONENT_INCLUDE_HPP
#define LIB_COMPONENT_RANDOMIZER_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/components/icomponent.hpp>

namespace lib::scene
{

    class RandomizerComponent : public IComponent
	{
	public:

        void update() override;
        void pause();
        void resume();
        void switchPause();

	};
}

#endif

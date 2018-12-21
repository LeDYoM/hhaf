#pragma once

#ifndef LIB_COMPONENT_RANDOMSYSTEM_INCLUDE_HPP
#define LIB_COMPONENT_RANDOMSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include "appservice.hpp"

namespace lib::core
{
    class Host;

    struct RandomBuffer
    {
        vector<size_type> numbers;
    };

    /**
    * This system is intended to be used to generate
    * a series of random numbers.
    */
    class RandomSystem final : public AppService
	{
	public:
        RandomSystem();
        ~RandomSystem() override;
        size_type getUInt() const;
        void generateRandomBuffer(RandomBuffer& dest, const size_type channel, const size_type size = 100U);

    private:
        class RandomSystemPrivate;
        uptr<RandomSystemPrivate> priv_;
	};
}

#endif

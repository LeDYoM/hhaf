#pragma once

#ifndef LIB_COMPONENT_RANDOMSYSTEM_INCLUDE_HPP
#define LIB_COMPONENT_RANDOMSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "appservice.hpp"

namespace lib::core
{
    class Host;

    /**
    * This system is intended to be used to generate
    * a series of random numbers.
    */
    class RandomSystem final : public AppService
	{
	public:
        RandomSystem(Host &host);
        ~RandomSystem() override;
        u32 getUInt(const size_type max = 1U, const size_type min = 0U) const;
    private:
        class RandomSystemPrivate;
        uptr<RandomSystemPrivate> priv_;
	};
}

#endif

#pragma once

#ifndef LIB_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <lib/system/appservice.hpp>

namespace lib::core
{
    /**
    * This system is intended to be used to generate
    * a series of random numbers.
    */
    class RandomSystem final : public HostedAppService
    {
    public:
        RandomSystem(core::SystemProvider &system_provider);
        ~RandomSystem() override;

        size_type getNext(const str& name, const size_type min, const size_type max);

    private:
        class RandomSystemPrivate;
        uptr<RandomSystemPrivate> priv_;
    };
}

#endif

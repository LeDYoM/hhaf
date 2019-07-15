#pragma once

#ifndef LIB_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <lib/system/appservice.hpp>
#include <lib/system/simulabledataprovider.hpp>

namespace lib::core
{
    /**
    * This system is intended to be used to generate
    * a series of random numbers.
    */
    class RandomSystem final : public AppService, public ISimulableDataProvider
    {
    public:
        RandomSystem();
        ~RandomSystem() override;
        void generateSimulableDataBuffer(SimulableDataBuffer& dest) override;

    private:
        class RandomSystemPrivate;
        uptr<RandomSystemPrivate> priv_;
    };
}

#endif

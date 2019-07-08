#pragma once

#ifndef LIB_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <lib/system/appservice.hpp>

namespace lib::core
{
    struct RandomBuffer
    {
        vector<size_type> numbers;
    };

    class IRandomSystem
    {
        virtual void generateRandomBuffer(RandomBuffer& dest, const size_type size = 100U) = 0;
    };

    /**
    * This system is intended to be used to generate
    * a series of random numbers.
    */
    class RandomSystem final : public AppService, IRandomSystem
    {
    public:
        RandomSystem();
        ~RandomSystem() override;
        void generateRandomBuffer(RandomBuffer& dest, const size_type size = 100U) override;

    private:
        class RandomSystemPrivate;
        uptr<RandomSystemPrivate> priv_;
    };
}

#endif

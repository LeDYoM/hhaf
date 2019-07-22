#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULABLE_DATA_PROVIDER_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULABLE_DATA_PROVIDER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <lib/system/appservice.hpp>

namespace lib::core
{
    using SimulableDataBuffer = vector<size_type>;

    /**
     * @brief Provide an interface to Simulable data.
     * This abstract class should be inherited from classes
     * that provide access to a @b SimulableDataBuffer, that is
     * can be wrapped by the @b SimulationSysten in order to
     * override it.
     */
    class ISimulableDataProvider
    {
    public:
        virtual void generateSimulableDataBuffer(SimulableDataBuffer& dest) = 0;
    };
}

#endif

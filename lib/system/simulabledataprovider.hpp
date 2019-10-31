#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULABLE_DATA_PROVIDER_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULABLE_DATA_PROVIDER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/str.hpp>

namespace lib::core
{

/**
     * @brief Provide an interface to get simulable data.
     * This abstract class should be inherited from classes
     * that provide access to a provider of data, that is
     * can be wrapped by the @b SimulationSysten in order to
     * override it.
     */
class ISimulableDataProvider
{
public:
    virtual size_type getNext(const str &name, const size_type min, const size_type max) = 0;
};
} // namespace lib::core

#endif

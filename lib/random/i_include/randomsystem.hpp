#pragma once

#ifndef LIB_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/str.hpp>
#include <lib/system/include/appservice.hpp>

namespace lib::sys
{
/**
* @brief This system is intended to be used to generate
* a series of random numbers.
*/
class RandomSystem final : public AppService
{
public:
    RandomSystem(sys::SystemProvider &system_provider);
    ~RandomSystem() override;

    size_type getNext(const str &name, const size_type min, const size_type max);

private:
    class RandomSystemPrivate;
    uptr<RandomSystemPrivate> priv_;
};
} // namespace lib::sys

#endif

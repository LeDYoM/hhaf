#pragma once

#ifndef HAF_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP
#define HAF_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/str.hpp>
#include <lib/system/include/appservice.hpp>

namespace haf::sys
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

    mtps::size_type getNext(const mtps::str&name, const mtps::size_type min, const mtps::size_type max);

private:
    class RandomSystemPrivate;
    mtps::uptr<RandomSystemPrivate> priv_;
};
} // namespace haf::sys

#endif

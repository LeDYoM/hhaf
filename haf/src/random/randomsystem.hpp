HAF_PRAGMA_ONCE
#ifndef HAF_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP
#define HAF_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include "system/system_base.hpp"

namespace haf::sys
{
/**
 * @brief This system is intended to be used to generate
 * a series of random numbers.
 */
class RandomSystem final : public SystemBase
{
public:
    RandomSystem(sys::SystemProvider& system_provider);
    ~RandomSystem();

    core::size_type getNext(const core::str& name,
                            const core::size_type min,
                            const core::size_type max);

private:
    class RandomSystemPrivate;
    core::PImplPointer<RandomSystemPrivate> priv_;
};
}  // namespace haf::sys

#endif

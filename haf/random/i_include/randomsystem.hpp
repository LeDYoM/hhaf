#ifndef HAF_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP
#define HAF_CORE_SYSTEM_RANDOMSYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/str.hpp>
#include <system/i_include/systembase.hpp>

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

    htps::size_type getNext(const htps::str& name,
                            const htps::size_type min,
                            const htps::size_type max);

private:
    class RandomSystemPrivate;
    htps::uptr<RandomSystemPrivate> priv_;
};
}  // namespace haf::sys

#endif

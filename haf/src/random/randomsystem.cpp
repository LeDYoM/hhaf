#include "randomsystem.hpp"
#include "system/system_provider.hpp"
#include "simulation/simulation_system.hpp"

#include <hlog/include/hlog.hpp>

#include <random>

using namespace htps;

namespace haf::sys
{
class RandomSystem::RandomSystemPrivate
{
public:
    std::random_device rd;
    std::mt19937 mt;

    RandomSystemPrivate() : mt{rd()} {}

    std::uniform_int_distribution<size_type> dist;

    template <typename T>
    T getNext()
    {
        return static_cast<T>(dist(mt));
    }
};

RandomSystem::RandomSystem(sys::SystemProvider& system_provider) :
    SystemBase{system_provider}, priv_{muptr<RandomSystemPrivate>()}
{}

RandomSystem::~RandomSystem() = default;

size_type RandomSystem::getNext(const str& name,
                                const size_type min,
                                const size_type max)
{
    const size_type next = priv_->getNext<size_type>();
    DisplayLog::verbose("RandomSystem: Raw number generator: ", next);
    LogAsserter::log_assert(min < max, "min (", min,
                            ") should be smaller than max (", max, ")");
    size_type filtered_next = (next % (max - min)) + min;
    DisplayLog::info("RandomSystem: Preselecting output: ", filtered_next);

    bool generated{systemProvider().system<SimulationSystem>().getNext(
        name, filtered_next)};
    (void)generated;

    return filtered_next;
}
}  // namespace haf::sys

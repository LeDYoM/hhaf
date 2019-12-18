#include "randomsystem.hpp"
#include <lib/system/systemprovider.hpp>
#include "simulationsystem.hpp"
#include <lib/include/liblog.hpp>

#include <random>

namespace lib::core
{
    class RandomSystem::RandomSystemPrivate
    {
    public:
        std::random_device rd;
        std::mt19937 mt;

        RandomSystemPrivate() : mt{ rd() } {}

        std::uniform_int_distribution<size_type> dist;

        template <typename T>
        T getNext()
        {
            return static_cast<T>(dist(mt));
        }
    };

    RandomSystem::RandomSystem(core::SystemProvider &system_provider)
        : HostedAppService{system_provider},
        priv_ { muptr<RandomSystemPrivate>() } {}

    RandomSystem::~RandomSystem() = default;

    size_type RandomSystem::getNext(const str& name, const size_type min, const size_type max)
    {
        const size_type next = priv_->getNext<size_type>();
        log_info("RandomSystem: Raw number generator: ", next);
        log_assert(min < max, "min (", min, ") should be smaller than max (", max, ")");
        size_type filtered_next = (next % (max - min)) + min;
        log_info("RandomSystem: Preselecting output: ", filtered_next);

        bool generated{systemProvider().simulationSystem().getNext(name, filtered_next)};

        return filtered_next;
    }
}

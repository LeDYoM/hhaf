#include "randomsystem.hpp"

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

    RandomSystem::RandomSystem()
        : AppService{ },
        priv_ { muptr<RandomSystemPrivate>() } {}

    RandomSystem::~RandomSystem() = default;

    size_type RandomSystem::getNext(const str& name, const size_type min, const size_type max)
    {
        const size_type next = priv_->getNext<size_type>();
        log_debug_info("RandomSystem: Raw number generator: ", next);
        assert_debug(min < max, "min (", min, ") should be smaller than max (", max, ")");
        const size_type filtered_next = (next % (max - min)) + min;
        log_debug_info("RandomSystem: Returning filtered output: ", filtered_next);
        return filtered_next;
    }
}

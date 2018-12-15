#include "randomsystem.hpp"
#include "host.hpp"

#include <lib/include/core/log.hpp>

#include <random>

namespace lib::core
{
    class RandomSystem::RandomSystemPrivate
    {
    public:
        std::random_device rd;
        std::mt19937 mt;

        RandomSystemPrivate() : mt{ rd() } {}

        std::uniform_int_distribution<int> dist;
    };

    RandomSystem::RandomSystem(Host &host)
        : AppService{ host },
        priv_ { muptr<RandomSystemPrivate>()
    } {}

    RandomSystem::~RandomSystem() = default;

    u32 RandomSystem::getUInt(const size_type max, const size_type min) const
    {
        log_debug_info("Asked for random number between ", min, " and ", max);
        assert_release(min != max, "The min and max parameters must be different");
        assert_release(max > min, "The max paramter must be greater than min");
        auto g(priv_->dist(priv_->mt) % (max - min));
        log_debug_info("\tGot ", g);
        log_debug_info("\tReturning ", min + g);
        return min + g;
    }
}

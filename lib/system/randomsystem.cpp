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

        size_type getUInt()
        {
            return static_cast<size_type>(dist(mt));
        }
    };

    RandomSystem::RandomSystem()
        : AppService{ },
        priv_ { muptr<RandomSystemPrivate>() } {}

    RandomSystem::~RandomSystem() = default;

    void RandomSystem::generateSimulableDataBuffer(SimulableDataBuffer & dest)
    {
        dest.resize(10U);

        for (auto& num_ref : dest)
        {
            num_ref = priv_->getUInt();
        }

        log_debug_info(dest);
    }
}

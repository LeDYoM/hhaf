#include "randomsystem.hpp"

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

        std::uniform_int_distribution<size_type> dist;

        size_type getUInt()
        {
            return static_cast<size_type>(dist(mt));
        }
    };

    RandomSystem::RandomSystem()
        : AppService{ },
        priv_ { muptr<RandomSystemPrivate>()
    } {}

    RandomSystem::~RandomSystem() = default;

    void RandomSystem::generateRandomBuffer(RandomBuffer & dest, const size_type channel, const size_type size)
    {
        dest.numbers.resize(size);

        if (channel != 0)
        {
            for (auto& num_ref : dest.numbers)
            {
                num_ref = priv_->getUInt();
            }
        }
        else
        {
            for (auto& num_ref : dest.numbers)
            {
                num_ref = priv_->getUInt();
            }
        }

        log_debug_info(dest.numbers);
    }
}

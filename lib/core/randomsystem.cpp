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

        std::uniform_int_distribution<size_type> dist;
    };

    RandomSystem::RandomSystem(Host &host)
        : AppService{ host },
        priv_ { muptr<RandomSystemPrivate>()
    } {}

    RandomSystem::~RandomSystem() = default;

    size_type RandomSystem::getUInt() const
    {
        return static_cast<size_type>(priv_->dist(priv_->mt));
    }

    void RandomSystem::generateRandomBuffer(RandomBuffer & dest, const size_type size)
    {
        dest.numbers.resize(size);

        for (auto& num_ref : dest.numbers)
        {
            num_ref = getUInt();
        }
    }
}

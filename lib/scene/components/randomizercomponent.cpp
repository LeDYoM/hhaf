#include "randomizercomponent.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/scene.hpp>

#include <random>

namespace lib::scene
{
    class RandomizerComponent::RandomizerPrivate
    {
    public:
        std::random_device rd;
        std::mt19937 mt;

        RandomizerPrivate()
            : mt{ rd() } {}

        std::uniform_int_distribution<int> dist;
    };

    RandomizerComponent::RandomizerComponent()
        : p_rPriv{ muptr<RandomizerPrivate>() } {}

    RandomizerComponent::~RandomizerComponent() = default;

    u32 RandomizerComponent::getUInt(const size_type max, const size_type min) const
    {
        log_debug_info("Asked for random number between ", min, " and ", max);
        assert_release(min != max, "The min and max parameters must be different");
        assert_release(max > min, "The max paramter must be greater than min");
        auto g(p_rPriv->dist(p_rPriv->mt) % (max - min));
        log_debug_info("\tGot ", g);
        log_debug_info("\tReturning ", min + g);
        return min + g;
    }
}

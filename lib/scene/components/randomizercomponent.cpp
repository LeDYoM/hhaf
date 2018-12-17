#include "randomizercomponent.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/core/randomsystem.hpp>

namespace lib::scene
{
    class RandomizerComponent::RandomizerPrivate
    {
    public:
    };

    RandomizerComponent::RandomizerComponent()
        : p_rPriv{ muptr<RandomizerPrivate>() } {}

    RandomizerComponent::~RandomizerComponent() = default;

    u32 RandomizerComponent::getUInt(const size_type max, const size_type min) const
    {
        return attachedNode()->randomSystem().getUInt(max, min);
    }
}

#include "randomizercomponent.hpp"
#include <lib/system/simulabledataprovider.hpp>
#include <lib/system/randomsystem.hpp>

#include <lib/include/liblog.hpp>
#include <lib/scene/scenenode.hpp>

namespace lib::scene
{
    class RandomizerComponent::RandomizerPrivate
    {
    public:
        constexpr RandomizerPrivate(core::ISimulableDataProvider& data_provider) noexcept
            : data_provider_{ data_provider }
        {
            assert_debug(std::addressof(data_provider_) != nullptr, "nullptr ISimulableDataProvider received");
        }

        ~RandomizerPrivate() = default;

        constexpr void ensureBufferAvailability()
        {
            if (consumed_ >= numbers_.numbers.end())
            {
                refillBuffer();
            }
            assert_debug(consumed_ <= numbers_.numbers.end(), "Error ensuring buffer availability");
        }

        constexpr size_type next()
        {
            ensureBufferAvailability();
            return *(consumed_++);
        }

    private:
        void refillBuffer()
        {
            log_debug_info("Call refillBuffer");
            data_provider_.generateSimulableDataBuffer(numbers_);
            consumed_ = numbers_.numbers.cbegin();
        }

        core::SimulableDataBuffer numbers_;
        core::SimulableDataBuffer::const_iterator consumed_{nullptr};
        core::ISimulableDataProvider& data_provider_;
        size_type buffer_size_{ 100U };
    };

    RandomizerComponent::RandomizerComponent() noexcept : priv_{ nullptr } {}

    RandomizerComponent::~RandomizerComponent() = default;

    u32 RandomizerComponent::getUInt(const size_type max, const size_type min) const
    {
        log_debug_info("Asked for random number between ", min, " and ", max);

        priv_->ensureBufferAvailability();

        assert_release(min != max, "The min and max parameters must be different");
        assert_release(max > min, "The max paramter must be greater than min");

        const auto next(priv_->next());
        log_debug_info("Fetch next element from random queue: ", next);
        const size_type generated(next % (max - min));
        log_debug_info("\tGot ", generated);
        log_debug_info("\tReturning ", min + generated);
        return min + generated;
    }

    void RandomizerComponent::onAttached()
    {
        if (attachedNode())
        {
            priv_ = muptr<RandomizerPrivate>(static_cast<core::ISimulableDataProvider&>(attachedNode()->randomSystem()));
        }
    }
}

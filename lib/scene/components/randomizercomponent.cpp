#include "randomizercomponent.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/core/randomsystem.hpp>
#include <lib/include/core/log.hpp>

namespace lib::scene
{
    class RandomizerComponent::RandomizerPrivate
    {
    public:
        constexpr RandomizerPrivate(core::RandomSystem& rSystem,
            const size_type buffer_size) noexcept
            : random_system_{ rSystem }, buffer_size_{ buffer_size }
        {
            assert_debug(std::addressof(rSystem) != nullptr, "nullptr RandomSystem received");
            assert_debug(buffer_size_ > 0U, "The buffer should be at least size 1");
        }

        constexpr void ensureBufferAvailability()
        {
            if (consumed_ >= numbers_.numbers.size())
            {
                refillBuffer();
            }
            assert_debug(consumed_ < numbers_.numbers.size(),"");
        }

        constexpr size_type next()
        {
            ensureBufferAvailability();
            return numbers_.numbers[consumed_++];
        }

    private:
        void refillBuffer()
        {
            log_debug_info("Called refillBuffer");
            log_debug_info("Size to refill: ", buffer_size_);
            random_system_.generateRandomBuffer(numbers_, buffer_size_);
            assert_release(numbers_.numbers.size() == buffer_size_, 
                "The size of the buffer is different from the buffer_size");
            consumed_ = 0U;
        }

        core::RandomBuffer numbers_;
        size_type consumed_{ 0U };
        core::RandomSystem& random_system_;
        size_type buffer_size_{ 100U };
    };

    RandomizerComponent::RandomizerComponent()
        : priv_{ nullptr } {}

    RandomizerComponent::~RandomizerComponent() = default;

    u32 RandomizerComponent::getUInt(const size_type max, const size_type min) const
    {
        log_debug_info("Asked for random number between ", min, " and ", max);

        priv_->ensureBufferAvailability();

        assert_release(min != max, "The min and max parameters must be different");
        assert_release(max > min, "The max paramter must be greater than min");
        const size_type generated(priv_->next() % (max - min));
        log_debug_info("\tGot ", generated);
        log_debug_info("\tReturning ", min + generated);
        return min + generated;
    }

    void RandomizerComponent::onAttached()
    {
        if (attachedNode())
        {
            priv_ = muptr<RandomizerPrivate>(attachedNode()->randomSystem(), 100U);
        }
    }
}

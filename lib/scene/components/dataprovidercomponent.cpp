#include "dataprovidercomponent.hpp"
#include <lib/system/simulabledataprovider.hpp>

#include <lib/include/liblog.hpp>
#include <lib/scene/scenenode.hpp>

namespace lib::scene
{
    class DataProviderComponent::DataProviderComponentPrivate
    {
    public:
        constexpr DataProviderComponentPrivate(core::ISimulableDataProvider& data_provider) noexcept
            : data_provider_{ data_provider }
        {
            assert_debug(std::addressof(data_provider_) != nullptr, "nullptr ISimulableDataProvider received");
        }

        ~DataProviderComponentPrivate() = default;

        constexpr void ensureBufferAvailability()
        {
            if (consumed_ >= numbers_.end())
            {
                // refill buffer
                log_debug_info("refilling buffer");
                data_provider_.generateSimulableDataBuffer(numbers_);
                consumed_ = numbers_.cbegin();
            }
            assert_debug(consumed_ <= numbers_.end(), "Error ensuring buffer availability");
        }

        constexpr size_type next()
        {
            ensureBufferAvailability();
            return *(consumed_++);
        }

    private:
#ifdef LIB_STORE_PLAY
#endif
        core::SimulableDataBuffer numbers_;
        core::SimulableDataBuffer::const_iterator consumed_{nullptr};
        core::ISimulableDataProvider& data_provider_;
        size_type buffer_size_{ 100U };
    };

    DataProviderComponent::DataProviderComponent() noexcept : priv_{ nullptr } {}

    DataProviderComponent::~DataProviderComponent() = default;

    u32 DataProviderComponent::getUInt(const size_type max, const size_type min) const
    {
        log_debug_info("Asked for random number between ", min, " and ", max);

        priv_->ensureBufferAvailability();

        assert_release(min != max, "The min and max parameters must be different");
        assert_release(max > min, "The max paramter must be greater than min");

        const auto next(priv_->next());
        log_debug_info("Fetch next element from queue: ", next);
        const size_type generated(next % (max - min));
        log_debug_info("\tGot ", generated);
        log_debug_info("\tReturning ", min + generated);
        return min + generated;
    }

    void DataProviderComponent::onAttached()
    {
        if (attachedNode())
        {
            priv_ = muptr<DataProviderComponentPrivate>(attachedNode()->simulableDataProvider());
        }
    }
}

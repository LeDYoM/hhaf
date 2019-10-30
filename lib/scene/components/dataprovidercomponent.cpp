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

        const str& name() const noexcept { return name_; }
        void setName(str name) { std::swap(name, name_); }

        core::ISimulableDataProvider& dataProvider() noexcept { return data_provider_; }
    private:
        core::ISimulableDataProvider& data_provider_;
        str name_;
    };

    DataProviderComponent::DataProviderComponent() noexcept : priv_{ nullptr } {}

    DataProviderComponent::~DataProviderComponent() = default;

    void DataProviderComponent::setName(str new_name)
    {
        priv_->setName(std::move(new_name));
    }

    const str& DataProviderComponent::name() const noexcept
    {
        return priv_->name();
    }

    u32 DataProviderComponent::getUInt(const size_type max, const size_type min) const
    {
        log_debug_info("Asked for random number between ", min, " and ", max);

        assert_release(min != max, "The min and max parameters must be different");
        assert_release(max > min, "The max paramter must be greater than min");

        const auto next(priv_->dataProvider().getNext(name(), min, max));
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

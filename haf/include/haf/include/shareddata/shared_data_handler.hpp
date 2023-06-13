HAF_PRAGMA_ONCE
#ifndef HAF_SHAREDDATA_SHAREDDATA_HANDLER_INCLUDE_HPP
#define HAF_SHAREDDATA_SHAREDDATA_HANDLER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/shareddata/address.hpp>
#include <haf/include/shareddata/ishared_data.hpp>

namespace haf::shdata
{

template <typename T, typename SharedDataRptr>
class SharedDataHandler
{
protected:
    explicit SharedDataHandler(htps::rptr<SharedDataRptr> shared_data) noexcept
        :
        shared_data_{shared_data}
    {}

    void reset()
    {
        address_ = Address{""};
        resetInternalData();
    }

    auto get(Address const& address)
    {
        createInternalDataIfEmpty();
        storeAddressOrReset(retrieve(address), address);
        return internalData();
    }

    htps::sptr<T> updateOrCreate(Address const& address)
    {
        createInternalDataIfEmpty();
        (void)(retrieve(address));
        address_ = address;
        createInternalDataIfEmpty();
        return internalData();
    }

    htps::sptr<T> update(Address const& address) { return get(address); }

    htps::sptr<T const> view(Address const& address) { return get(address); }

    bool retrieve(Address const& address) const
    {
        return shared_data_->retrieve(address, *internal_data_);
    }

    bool store()
    {
        auto const result{shared_data_->store(address_, *internal_data_)};
        return result;
    }

    htps::sptr<T const> internalData() const noexcept { return internal_data_; }
    htps::sptr<T> internalData() noexcept { return internal_data_; }

    void resetInternalData() { internal_data_.reset(); }

private:
    void storeAddressOrReset(bool const result, Address const& address)
    {
        if (result)
        {
            address_ = address;
        }
        else
        {
            reset();
        }
    }

    htps::sptr<T> create() { return htps::msptr<T>(); }

    void createInternalData() { internal_data_ = create(); }

    void createInternalDataIfEmpty()
    {
        if (!internal_data_)
        {
            createInternalData();
        }
    }

    Address address_{""};
    htps::sptr<T> internal_data_{nullptr};
    htps::rptr<SharedDataRptr> shared_data_{nullptr};
};

}  // namespace haf::shdata

#endif

#ifndef HAF_SHAREDDATA_SHAREDDATA_HANDLER_INCLUDE_HPP
#define HAF_SHAREDDATA_SHAREDDATA_HANDLER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/shareddata/address.hpp>
#include <haf/include/shareddata/ishared_data.hpp>

#include <hlog/include/hlog.hpp>

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

    htps::sptr<T> create() { return htps::msptr<T>(); }

    void createInternalData() { internal_data_ = create(); }

    void createInternalDataIfEmpty()
    {
        if (!internal_data_)
        {
            createInternalData();
        }
    }

    void reset()
    {
        DisplayLog::error("Invalid address");
        address_ = Address{""};
        internal_data_.reset();
    }

    htps::sptr<T const> view(Address const& address)
    {
        if (internal_data_ == nullptr)
        {
            internal_data_ = htps::msptr<T>();
        }

        auto const result{shared_data_->retrieve(address, *internal_data_)};

        if (result)
        {
            address_ = address;
        }
        else
        {
            DisplayLog::error("Invalid address");
            address_ = Address{""};
            internal_data_.reset();
        }

        return internal_data_;
    }

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

    bool retrieve(Address const& address) const
    {
        return shared_data_->retrieve(address, *internal_data_);
    }

    bool store()
    {
        auto const result{shared_data_->store(address_, *internal_data_)};
        if (!result)
        {
            DisplayLog::debug("Cannot store!");
        }
        return result;
    }

    Address address_{""};
    htps::sptr<T> internal_data_{nullptr};
    htps::rptr<SharedDataRptr> shared_data_{nullptr};
};

}  // namespace haf::shdata

#endif

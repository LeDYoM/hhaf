#ifndef HAF_SHAREDDATA_SHAREDDATA_HANDLER_INCLUDE_HPP
#define HAF_SHAREDDATA_SHAREDDATA_HANDLER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/shareddata/address.hpp>
#include <haf/include/shareddata/ishared_data.hpp>

#include <hlog/include/hlog.hpp>

namespace haf::shdata
{

template <typename T>
class SharedDataHandler
{
protected:
    explicit SharedDataUpdater(htps::rptr<ISharedData> shared_data) noexcept :
        shared_data_{shared_data}
    {}

    htps::sptr<T> create()
    {
        return htps::mptr<T>();
    }

    void createInternalData()
    {
        internal_data_ = create();
    }

    void createInternalDataIfEmpty()
    {
        if (!internal_data_)
        {
            createInternalData();
        }
    }

    htps::sptr<T> update(Address const& address)
    {
        createInternalDataIfEmpty();

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

    bool commit()
    {
        if (internal_data_ != nullptr)
        {
            bool const result = shared_data_->store(address_, *internal_data_);
            internal_data_.reset();

            if (!result)
            {
                DisplayLog::debug("Cannot store!");
            }
            return result;
        }
        return false;
    }

    bool rollback()
    {
        if (internal_data_ != nullptr)
        {
            internal_data_.reset();
            return true;
        }
        return false;
    }

    ~SharedDataUpdater() { (void)commit(); }

private:
    Address address_{""};
    htps::sptr<T> internal_data_{nullptr};
    htps::rptr<ISharedData> shared_data_{nullptr};
};

}  // namespace haf::shdata

#endif

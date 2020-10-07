#pragma once

#ifndef HAF_SHAREDDATA_SHAREDDATA_UPDATER_INCLUDE_HPP
#define HAF_SHAREDDATA_SHAREDDATA_UPDATER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/shareddata/include/ishareable.hpp>
#include <haf/shareddata/include/address.hpp>
#include <haf/shareddata/include/shareddata.hpp>

#include <hlog/include/hlog.hpp>

namespace haf::shdata
{

template <typename T>
class SharedDataUpdater : public SharedData
{
public:
    /*
        template <typename T>
        T* update(Address const& address, T& data)
        {
            bool const result = retrieve(address, data);
            if (result)
            {
                internal_data_ = &data;
                address_       = address;
            }
            return dynamic_cast<T*>(internal_data_);
        }
    */
    mtps::sptr<T>  update(Address const& address)
    {
        if (!internal_data_)
        {
            internal_data_ = mtps::msptr<T>();
        }

        bool const result = retrieve(address, *internal_data_);
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
            bool const result = store(address_, *internal_data_);
            internal_data_    = nullptr;

            if (!result)
            {
                DisplayLog::debug("Cannot store!");
            }
            return result;
        }
        return false;
    }

    ~SharedDataUpdater() override { (void)commit(); }

private:
    Address address_{""};
    mtps::sptr<T> internal_data_{nullptr};
};

}  // namespace haf::shdata

#endif

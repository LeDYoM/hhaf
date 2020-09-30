#pragma once

#ifndef HAF_SHAREDDATA_DATA_WRAPPER_INCLUDE_HPP
#define HAF_SHAREDDATA_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/shareddata/include/ishareable.hpp>
#include <haf/shareddata/include/address.hpp>

#include <hlog/include/hlog.hpp>

namespace haf::shdata
{
/**
 * @brief Component to provide access to data resources.
 */
class SharedData : public sys::IDataWrapper
{
public:
    using sys::IDataWrapper::IDataWrapper;

    bool store(Address const& address, IShareable const& data);
    [[nodiscard]] bool retrieve(Address const& address, IShareable& data);

    [[nodiscard]] bool isEmpty();
    bool makeEmpty();
};

class SharedDataUpdater : public SharedData
{
public:
    template <typename T>
    T* update(Address const& address)
    {
        T data;

        bool const result = retrieve(address, data);
        if (result)
        {
            internal_data_ = &data;
            address_       = address;
        }
        return dynamic_cast<T*>(internal_data_);
    }

    template <typename T>
    T const* view(Address const& address, T& data)
    {
        bool const result{retrieve(address, data)};
        if (result)
        {
            internal_data_ = &data;
            address_       = address;
        }
        return dynamic_cast<T const*>(internal_data_);
    }

    [[nodiscard]] bool isEmpty();
    bool makeEmpty();

    ~SharedDataUpdater() override
    {
        if (internal_data_ != nullptr)
        {
            bool const result = store(address_, *internal_data_);
            if (!result)
            {
                DisplayLog::debug("Cannot store!");
            }
            internal_data_ = nullptr;
        }
    }

private:
    Address address_{""};
    IShareable* internal_data_{nullptr};
};

}  // namespace haf::shdata

#endif

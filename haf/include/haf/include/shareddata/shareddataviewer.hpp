#ifndef HAF_SHAREDDATA_SHAREDDATA_VIEWER_INCLUDE_HPP
#define HAF_SHAREDDATA_SHAREDDATA_VIEWER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/system/idatawrapper.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/shareddata/address.hpp>
#include <haf/include/shareddata/shareddata.hpp>

#include <hlog/include/hlog.hpp>

namespace haf::shdata
{
template <typename T>
class SharedDataViewer : public SharedData
{
public:
    htps::sptr<T const> view(Address const& address)
    {
        if (internal_data_ == nullptr)
        {
            internal_data_ = htps::msptr<T>();
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

private:
    Address address_{""};
    htps::sptr<T> internal_data_{nullptr};
};

}  // namespace haf::shdata

#endif

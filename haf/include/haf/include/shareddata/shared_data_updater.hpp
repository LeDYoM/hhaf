#ifndef HAF_SHAREDDATA_SHAREDDATA_UPDATER_INCLUDE_HPP
#define HAF_SHAREDDATA_SHAREDDATA_UPDATER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/shareddata/address.hpp>
#include <haf/include/shareddata/ishared_data.hpp>
#include <haf/include/shareddata/shared_data_handler.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::shdata
{

template <typename T>
class SharedDataUpdater : public SharedDataHandler<T, ISharedData>
{
    using BaseClass = SharedDataHandler<T, ISharedData>;

public:
    explicit SharedDataUpdater(htps::rptr<ISharedData> shared_data) noexcept :
        BaseClass{shared_data}
    {}

    htps::sptr<T> update(Address const& address)
    {
        BaseClass::createInternalDataIfEmpty();

        auto const result{BaseClass::retrieve(address)};
        BaseClass::storeAddressOrReset(result, address);
        return BaseClass::internal_data_;
    }

    bool commit()
    {
        if (BaseClass::internal_data_ != nullptr)
        {
            bool const result = BaseClass::store();
            BaseClass::internal_data_.reset();
            return result;
        }
        return false;
    }

    bool rollback()
    {
        if (BaseClass::internal_data_ != nullptr)
        {
            BaseClass::internal_data_.reset();
            return true;
        }
        return false;
    }

    ~SharedDataUpdater() { (void)commit(); }
};

}  // namespace haf::shdata

#endif

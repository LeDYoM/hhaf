HTPS_PRAGMA_ONCE
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

    using BaseClass::update;
    using BaseClass::updateOrCreate;

    bool commit()
    {
        if (BaseClass::internalData() != nullptr)
        {
            bool const result{BaseClass::store()};
            BaseClass::resetInternalData();
            return result;
        }
        return false;
    }

    bool rollback()
    {
        if (BaseClass::internalData() != nullptr)
        {
            BaseClass::resetInternalData();
            return true;
        }
        return false;
    }

    ~SharedDataUpdater() { (void)commit(); }
};

}  // namespace haf::shdata

#endif

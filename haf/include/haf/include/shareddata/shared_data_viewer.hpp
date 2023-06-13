HAF_PRAGMA_ONCE
#ifndef HAF_SHAREDDATA_SHAREDDATA_VIEWER_INCLUDE_HPP
#define HAF_SHAREDDATA_SHAREDDATA_VIEWER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/shareddata/address.hpp>
#include <haf/include/shareddata/ishared_data.hpp>
#include <haf/include/shareddata/shared_data_handler.hpp>

#include <hlog/include/hlog.hpp>

namespace haf::shdata
{
template <typename T>
class SharedDataViewer : public SharedDataHandler<T, ISharedData const>
{
    using BaseClass = SharedDataHandler<T, ISharedData const>;

public:
    explicit SharedDataViewer(
        htps::rptr<ISharedData const> shared_data) noexcept :
        BaseClass{shared_data}
    {}

    using BaseClass::view;
};

}  // namespace haf::shdata

#endif

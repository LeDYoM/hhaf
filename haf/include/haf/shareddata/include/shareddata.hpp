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

}  // namespace haf::shdata

#endif

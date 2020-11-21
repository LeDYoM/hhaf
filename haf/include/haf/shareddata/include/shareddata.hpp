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
 * @brief DataWrapper to provide access to data resources.
 * This wrapper can be used standalone or as a base class of other wrappers.
 */
class SharedData : public sys::IDataWrapper
{
public:
    using BaseClass = sys::IDataWrapper;

    /**
     * @brief Use base class constructors.
     */
    using BaseClass::BaseClass;

    /**
     * @brief Store an IShareable data element in the system. If the address
     * does not exist, it will be created.
     * @param address The address where to add the element.
     * @param data Element to store.
     * @return true Successfully stored.
     * @return false Not stored.
     */
    bool store(Address const& address, IShareable const& data);

    /**
     * @brief Retrieve an element from the system.
     * @param address Address where to look for the element.
     * @param data Data where to retrieve the element.
     * @return true Successfully retrieved.
     * @return false Error retrieving the element.
     */
    [[nodiscard]] bool retrieve(Address const& address, IShareable& data);

    /**
     * @brief Ask if the system contains any data.
     * 
     * @return true 
     * @return false 
     */
    [[nodiscard]] bool isEmpty();
    bool makeEmpty();
};

}  // namespace haf::shdata

#endif

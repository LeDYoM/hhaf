HAF_PRAGMA_ONCE
#ifndef HAF_SHAREDDATA_DATA_WRAPPER_INCLUDE_HPP
#define HAF_SHAREDDATA_DATA_WRAPPER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/shareddata/address.hpp>

namespace haf::shdata
{
/**
 * @brief SubSystem to provide access to data resources.
 * This wrapper can be used standalone or as a base class of other wrappers.
 */
class ISharedData
{
protected:
    virtual ~ISharedData() = default;

public:
    /**
     * @brief Store an IShareable data element in the system. If the address
     * does not exist, it will be created.
     * @param address The address where to add the element.
     * @param data Element to store.
     * @return true Successfully stored.
     * @return false Not stored.
     */
    virtual bool store(Address const& address, IShareable const& data) = 0;

    /**
     * @brief Retrieve an element from the system.
     * @param address Address where to look for the element.
     * @param data Data where to retrieve the element.
     * @return true Successfully retrieved.
     * @return false Error retrieving the element.
     */
    [[nodiscard]] virtual bool retrieve(Address const& address,
                                        IShareable& data) const = 0;

    /**
     * @brief Ask if the system contains any data.
     *
     * @return true
     * @return false
     */
    [[nodiscard]] virtual bool isEmpty() const noexcept = 0;
    virtual bool makeEmpty()                            = 0;
};

}  // namespace haf::shdata

#endif

#ifndef HAF_SYSTEM_DATA_WRAPPER_CREATOR_INCLUDE_HPP
#define HAF_SYSTEM_DATA_WRAPPER_CREATOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/system/idatawrapper.hpp>
#include <haf/include/utils/attachable_manager.hpp>

namespace haf::sys
{
class SystemAccess;
}

namespace haf::sys
{
/**
 * @brief Class to create @b IDataWrapper (s) instances.
 * DataWrappers are stand alone objects, not components that get updated.
 * You can also create as much as you need for a given type.
 * @see IDataWrapper
 * @see IComponent
 */
class DataWrapperCreator : public utils::AttachableManager<IDataWrapper>
{
    using BaseClass = utils::AttachableManager<IDataWrapper>;

public:
    using BaseClass::BaseClass;

    /**
     * @brief Fetch a specific type of data wrapper.
     * 
     * @tparam T Concrete type of the data wrapper.
     * @return htps::uptr<T> containing the data wrapper.
     */
    template <typename T>
    htps::uptr<T> dataWrapper() const
    {
        return BaseClass::create<T>();
    }
};

}  // namespace haf::sys

#endif

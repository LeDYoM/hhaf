#ifndef HAF_SYSTEM_DATA_WRAPPER_CREATOR_INCLUDE_HPP
#define HAF_SYSTEM_DATA_WRAPPER_CREATOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/utils/include/attachable_manager.hpp>
#include <haf/scene/include/interface_getter.hpp>

namespace haf::sys
{
class SystemAccess;
}

namespace haf::sys
{
/**
 * @brief Class to create @b IDataWrapper (s) instances.
 * DataWrappers are stand alone objects, not components that interact with
 * their containers. For active content see @b IComponent.
 * @see IDataWrapper
 * @see IComponent
 */
class DataWrapperCreator : public utils::AttachableManager<IDataWrapper>
{
public:
    using BaseClass = utils::AttachableManager<IDataWrapper>;

    using BaseClass::AttachableManager;

    /// Fetch a specific type of data wrapper.
    /// @paramt T Concrete type of the data wrapper.
    /// @return \b htps::uptr<T> containing the data wrapper.
    template <typename T>
    htps::uptr<T> dataWrapper() const
    {
        return create<T>();
    }
};
}  // namespace haf::sys

#endif

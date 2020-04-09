#pragma once

#ifndef HAF_SCENE_DATA_WRAPPER_CREATOR_INCLUDE_HPP
#define HAF_SCENE_DATA_WRAPPER_CREATOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/utils/include/attachable_manager.hpp>

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
 */
class DataWrapperCreator : public AttachableManager<IDataWrapper>
{
public:
    using BaseClass = AttachableManager<IDataWrapper>;

    using BaseClass::AttachableManager;

    /// Fetch a specific type of data wrapper.
    /// @paramt T Concrete type of the data wrapper.
    /// @return \b mtps::uptr<T> containing the data wrapper.
    template <typename T>
    mtps::uptr<T> dataWrapper() const
    {
        return create<T>();
    }
};
}  // namespace haf::sys

#endif

#pragma once

#ifndef LIB_SCENE_DATA_WRAPPER_CREATOR_INCLUDE_HPP
#define LIB_SCENE_DATA_WRAPPER_CREATOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/include/idatawrapper.hpp>
#include <lib/system/include/attachable_manager.hpp>

namespace lib::sys
{
class SystemAccess;
}

namespace lib::sys
{
/**
 * @brief Class to create @b IDataWrapper (s) instances.
 * DataWrappers are stand alone objects, not components that interact with
 * their containers. For active content see @b IComponent.
 */
class DataWrapperCreator : public AttachableManager<IDataWrapper, true>
{
public:
    using BaseClass = AttachableManager<IDataWrapper, true>;

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
} // namespace lib::sys

#endif

#pragma once

#ifndef LIB_SCENE_DATA_WRAPPER_CREATOR_INCLUDE_HPP
#define LIB_SCENE_DATA_WRAPPER_CREATOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/include/idatawrapper.hpp>
#include <lib/system/include/attachable_manager.hpp>

namespace lib::sys
{
    class SystemAccess;
}

namespace lib::scene
{
/**
 * @brief Class to create @b IDataWrapper (s) instances.
 * DataWrappers are stand alone objects, not components that interact with
 * their containers. For active content see @b IComponent.
 */
class DataWrapperCreator : public sys::AttachableManager<IDataWrapper, true>
{
public:
    using BaseClass = sys::AttachableManager<IDataWrapper, true>;

    using BaseClass::AttachableManager;

    /// Fetch a specific type of data wrapper.
    /// @paramt T Concrete type of the data wrapper.
    /// @return \b uptr<T> containing the data wrapper.
    template <typename T>
    uptr<T> dataWrapper() const
    {
        return create<T>();
    }
};
} // namespace lib::scene

#endif

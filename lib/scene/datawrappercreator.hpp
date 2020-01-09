#pragma once

#ifndef LIB_SCENE_DATA_WRAPPER_CREATOR_INCLUDE_HPP
#define LIB_SCENE_DATA_WRAPPER_CREATOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "idatawrapper.hpp"

namespace lib::scene
{
class SceneNode;

///
/// @brief Class to create @b IDataWrapper (s) instances.
/// DataWrappers are stand alone objects, not components that interact with
/// their containers. For active content see @b IComponent.
class DataWrapperCreator
{
public:
    /// Constructor.
    /// @param scene_node Node to fetch the data to be wrapped.
    constexpr DataWrapperCreator(rptr<SceneNode> scene_node) noexcept
        : scene_node_{std::move(scene_node)} {}

    /// Destructor.
    virtual ~DataWrapperCreator();

    /// Fetch a specific type of data wrapper.
    /// @paramt T Concrete type of the data wrapper.
    /// @return \b uptr<T> containing the data wrapper.
    template <typename T>
    uptr<T> dataWrapper()
    {
        static_assert(std::is_base_of_v<IDataWrapper, T>, "You can only use this "
                                                          "function with types derived from IDataWrapper");
        uptr<T> result = muptr<T>();
        initialize(result.get());
        return result;
    }

private:
    void initialize(IDataWrapper *const dw);
    const rptr<SceneNode> scene_node_;
};
} // namespace lib::scene

#endif

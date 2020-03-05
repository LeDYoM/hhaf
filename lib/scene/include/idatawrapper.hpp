#pragma once

#ifndef LIB_SCENE_IDATA_WRAPPER_INCLUDE_HPP
#define LIB_SCENE_IDATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/include/attachable.hpp>

namespace lib::scene
{
class SceneNode;

/**
 * @brief Base class for classes that provide some kind of access to specific
 *  data.
 * The idea is that when an scene node needs access to specific data it wraps
 * it in some subclass of this class that will bring getters and setter to
 * some specific data via a scene node.
 * The @b IDataWrapper is not stored anywhere internally.
 */
class IDataWrapper : public Attachable<SceneNode>
{
private:
    friend class DataWrapperCreator;
};
} // namespace lib::scene

#endif

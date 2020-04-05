#pragma once

#ifndef LIB_SCENE_ICOMPONENT_INCLUDE_HPP
#define LIB_SCENE_ICOMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/utils/include/attachable.hpp>

namespace haf::scene
{
class SceneNode;

/// Base class for all components attached to a scene node.
class IComponent : public sys::Attachable<SceneNode>
{
public:
    using AttachedNodeType = sys::Attachable<SceneNode>::AttachedNodeType;

    /**
     * @brief Interface to be implemented to update the component
     */
    virtual void update() {}

    /// Destructor
    ~IComponent() override {}

private:
    friend class ComponentContainer;
};

template <typename T1, typename T2>
class IComponentMixin : public IComponent
{
    virtual void update() override
    {
        T1::update();
        T2::update();
    }
};
} // namespace haf::scene

#endif

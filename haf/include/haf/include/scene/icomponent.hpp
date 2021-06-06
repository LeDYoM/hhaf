#ifndef HAF_SCENE_ICOMPONENT_INCLUDE_HPP
#define HAF_SCENE_ICOMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/utils/attachable.hpp>

namespace haf::scene
{
class SceneNode;

/// Base class for all components attached to a scene node.
template <bool WithUpdate>
class IComponentBase;

template <>
class IComponentBase<false> : public utils::Attachable<SceneNode>
{
public:
    using AttachedNodeType = utils::Attachable<SceneNode>::AttachedNodeType;

    /// Destructor
    ~IComponentBase() override {}
};

template <>
class IComponentBase<true> : public utils::Attachable<SceneNode>
{
public:
    using AttachedNodeType = utils::Attachable<SceneNode>::AttachedNodeType;

    /**
     * @brief Interface to be implemented to update the component
     */
    virtual void update() {}

    /// Destructor
    ~IComponentBase() override {}
};

using IComponent = IComponentBase<true>;

template <typename T1, typename T2>
class IComponentMixin : public IComponent
{
    virtual void update() override
    {
        T1::update();
        T2::update();
    }
};
}  // namespace haf::scene

#endif

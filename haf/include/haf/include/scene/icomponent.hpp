#ifndef HAF_SCENE_ICOMPONENT_INCLUDE_HPP
#define HAF_SCENE_ICOMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/utils/attachable.hpp>

namespace haf::scene
{
class SceneNode;

class IComponent : public utils::Attachable<SceneNode>
{
public:
    using AttachedNodeType = utils::Attachable<SceneNode>::AttachedNodeType;

    /**
     * @brief Interface to be implemented to update the component
     */
    virtual void update() {}

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
}  // namespace haf::scene

#endif

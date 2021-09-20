#ifndef HAF_SCENE_ICOMPONENT_INCLUDE_HPP
#define HAF_SCENE_ICOMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/types/basic_types.hpp>
#include <haf/include/utils/attachable.hpp>

namespace haf::scene
{
class SceneNode;
}

namespace haf::component
{

class IComponent : public utils::Attachable<scene::SceneNode>
{
public:
    using AttachedNodeType =
        utils::Attachable<scene::SceneNode>::AttachedNodeType;

    /**
     * @brief Interface to be implemented to update the component
     */
    virtual void update() {}
};

}  // namespace haf::component

#endif

#ifndef HAF_SCENE_VISIBILITY_SELECTOR_INCLUDE_HPP
#define HAF_SCENE_VISIBILITY_SELECTOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <haf/include/scene/scenenode.hpp>
#include <haf/include/scene/icomponent.hpp>

namespace haf::scene
{
/// Class representing a SceneNode that will have only one visible child.
class VisibilitySelectorComponent : public IComponent
{
public:
    void configure(htps::size_type first_index);
    void show(htps::size_type index, bool force = false);

private:
    void hideAll();

    htps::size_type active_index{0U};
};

}  // namespace haf::scene

#endif

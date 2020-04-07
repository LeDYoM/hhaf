#pragma once

#ifndef HAF_SCENE_VISIBILITY_SELECTOR_INCLUDE_HPP
#define HAF_SCENE_VISIBILITY_SELECTOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/scene/include/scenenode.hpp>

namespace haf::scene
{
/// Class representing a SceneNode that will have only one visible child.
class VisibilitySelectorComponent : public IComponent
{
public:
    void configure(mtps::size_type first_index);
    void show(mtps::size_type index, bool force = false);

private:
    void hideAll();

    mtps::size_type active_index{0U};
};

class VisibilitySelector : public SceneNode
{
public:
    using SceneNode::SceneNode;

    void configure(mtps::size_type first_index);
    void show(mtps::size_type index, bool force = false);
};

} // namespace haf::scene::nodes

#endif

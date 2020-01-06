#pragma once

#ifndef LIB_SCENE_VISIBILITY_SELECTOR_INCLUDE_HPP
#define LIB_SCENE_VISIBILITY_SELECTOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/scene/scenenode.hpp>

namespace lib::scene::nodes
{
/// Class representing a SceneNode that will have only one visible child.
class VisibilitySelector : public SceneNode
{
public:
    using BaseClass = SceneNode;

    VisibilitySelector(SceneNode *parent, str name);
    ~VisibilitySelector() override;

    void configure(size_type first_index);
    void show(size_type index, bool force = false);

private:
    void hideAll();

    size_type active_index{0U};
};
} // namespace lib::scene::nodes

#endif

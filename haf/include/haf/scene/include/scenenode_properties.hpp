#pragma once

#ifndef HAF_SCENE_SCENENODE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_PROPERTIES_INCLUDE_HPP

#include <mtypes/include/grouping_property.hpp>

namespace haf::scene
{
struct Visible
{
    using value_type = bool;
};

using SceneNodeProperties = mtps::PropertyGroup<Visible>;

}  // namespace haf::scene

#endif

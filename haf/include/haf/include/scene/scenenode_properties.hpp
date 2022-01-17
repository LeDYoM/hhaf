#ifndef HAF_SCENE_SCENENODE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_PROPERTIES_INCLUDE_HPP

#include <haf/include/types/property_group.hpp>

namespace haf::scene
{
struct Visible : PropertyStateBase<bool> {};

using SceneNodeProperties = types::PropertyGroup<Visible>;

}  // namespace haf::scene

#endif

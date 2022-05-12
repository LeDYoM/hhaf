HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENENODE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_PROPERTIES_INCLUDE_HPP

#include <htypes/include/property_group.hpp>

namespace haf::scene
{
struct Visible : htps::PropertyStateBase<bool> {};

using SceneNodeProperties = htps::PropertyGroup<Visible>;

}  // namespace haf::scene

#endif

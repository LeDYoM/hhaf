#ifndef HAF_SCENE_SCENENODE_PROPERTIES_INCLUDE_HPP
#define HAF_SCENE_SCENENODE_PROPERTIES_INCLUDE_HPP

#include <htypes/include/grouping_property.hpp>

namespace haf::scene
{
struct Visible
{
    using value_type = bool;
};

using SceneNodeProperties = htps::PropertyGroup<Visible>;

}  // namespace haf::scene

#endif

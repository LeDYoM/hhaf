HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_COMPONENT_INCLUDE_HPP
#define HAF_SCENE_SCENE_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>
#include <haf/include/scene_components/transformation_component.hpp>
#include <haf/include/scene_components/scene_nodes_component.hpp>
#include <haf/include/scene_components/debug_camera_component.hpp>

namespace haf::scene
{
class HAF_API SceneComponent final
    : public component::ComponentBase<"SceneComponent",
                                      SceneNodesComponent,
                                      TransformationComponent,
                                      DebugCameraComponent>
{};

}  // namespace haf::scene

#endif

#include <haf/include/scene_components/scene_render_properties_component.hpp>
#include <haf/include/component/component_definition.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/scene/scene_node.hpp>

#include "system/get_system.hpp"
#include "scene/scene_manager.hpp"

using namespace haf::core;

namespace haf::scene
{
struct SceneRenderPropertiesComponent::PrivateComponentData
{
};

SceneRenderPropertiesComponent::SceneRenderPropertiesComponent() :
    m_p{make_pimplp<PrivateComponentData>()}
{}

SceneRenderPropertiesComponent::~SceneRenderPropertiesComponent() = default;

void SceneRenderPropertiesComponent::onAttached()
{
}

}  // namespace haf::scene

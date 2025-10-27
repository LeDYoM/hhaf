#include <haf/include/component/component.hpp>
#include <haf/include/system/subsystem_view.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene_render_context.hpp>
#include <haf/include/scene/iscene_render_context_provider.hpp>

using namespace haf::core;
using namespace haf::scene;

namespace haf::component
{
SceneRenderContext& Component::sceneRenderContext()
{
    return attachedNode()
        ->subSystem<scene::ISceneRenderContextProvider>()
        ->sceneRenderContext();
}

SceneRenderContext const& Component::sceneRenderContext() const
{
    return attachedNode()
        ->subSystem<scene::ISceneRenderContextProvider>()
        ->sceneRenderContext();
}

str Component::staticTypeName() const noexcept
{
    return "Component";
}

ComponentOrder::Value Component::componentOrder() const noexcept
{
    return ComponentOrder::NoOrder;
}

}  // namespace haf::component

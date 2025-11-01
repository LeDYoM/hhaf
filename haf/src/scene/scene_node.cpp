#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_components/camera_component.hpp>

#include <haf/include/scene/iscene_render_context_provider.hpp>
#include <haf/include/scene/scene_render_context.hpp>

using namespace haf::core;

namespace haf::scene
{
SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{htps::move(name)},
    SceneNodeParent{parent},
    SceneNodes{this},
    sys::SystemAccess{parent != nullptr ? &(parent->isystemProvider())
                                        : nullptr},
    component::ComponentContainer{this},
    sys::SubSystemViewer{&isystemProvider()}
{
    component<Transformation>();
}

SceneNode::~SceneNode() = default;

void SceneNode::clearAll()
{
    clearSceneNodes();
}


}  // namespace haf::scene

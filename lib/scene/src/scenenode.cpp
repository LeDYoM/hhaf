#include "scenenode.hpp"

namespace lib::scene
{
SceneNode::SceneNode(rptr<SceneNode> parent, str name)
    : sys::HasName{std::move(name)},
      SceneNodeParent{parent},
      SceneNodes{this}, Renderizables{this},
      DataWrapperCreator{this}, ComponentContainer{this},
      SceneManagerAccessor{parent != nullptr ? &(parent->sceneManager()) : nullptr},
      visible{true}
{
}

SceneNode::~SceneNode() = default;

void SceneNode::render(bool parentTransformationChanged)
{
    if (visible())
    {
        // Update the node components
        updateComponents();

        // Update node
        update();

        parentTransformationChanged |= updateTransformIfNecessary();

        if (parentTransformationChanged)
        {
            updateGlobalTransformation(
                parent() ? parent()->globalTransform() : Transform::Identity);
        }

        updateRenderizables();
        renderGroups(parentTransformationChanged);
    }
}

void SceneNode::clearAll()
{
    clearSceneNodes();
    clearComponents();
}

} // namespace lib::scene

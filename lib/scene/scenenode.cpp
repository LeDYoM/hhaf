#include "scenenode.hpp"
#include "scene.hpp"

#include <lib/scene/renderizable.hpp>

#include <lib/include/liblog.hpp>

#include <lib/system/scenemanager.hpp>
#include "scenenodeblob.hpp"

namespace lib::scene
{
SceneNode::SceneNode(rptr<SceneNode> parent, str name)
    : sys::HasName{std::move(name)},
      SceneNodeParent{parent, parent != nullptr ? (parent->parentScene()) : nullptr},
      SceneNodes{this},
      DataWrapperCreator{this}, ComponentContainer{this}, SceneNodeBlob{*this},
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

        postUpdateComponents();
        renderGroups(parentTransformationChanged);
    }
}

void SceneNode::clearAll()
{
    clearSceneNodes();
    clearComponents();
}

} // namespace lib::scene

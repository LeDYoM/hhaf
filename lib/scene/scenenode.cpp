#include "scenenode.hpp"
#include "scene.hpp"

#include <lib/scene/renderizable.hpp>

#include <lib/include/liblog.hpp>

#include <lib/system/scenemanager.hpp>
#include "scenenodeblob.hpp"

namespace lib::scene
{
SceneNode::SceneNode(SceneNode *const parent, str name)
    : sys::HasName{std::move(name)}, SceneNodes{this},
      DataWrapperCreator{this}, ComponentContainer{this}, SceneNodeBlob{*this},
      visible{true}, m_parent{parent}
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
                m_parent ? m_parent->globalTransform() : Transform::Identity);
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

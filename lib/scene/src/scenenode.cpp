#include "scenenode.hpp"
#include "scenemanager.hpp"
#include <lib/system/i_include/get_system.hpp>

using namespace mtps;

namespace lib::scene
{
SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{std::move(name)},
    SceneNodeParent{parent},
    SceneNodes{this},
    Renderizables{this},
    sys::DataWrapperCreator{this},
    ComponentContainer{this},
    sys::SystemAccess{parent != nullptr ? &(parent->isystemProvider())
                                        : nullptr},
    visible{true}
{}

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
            updateGlobalTransformation(parent() ? parent()->globalTransform()
                                                : Transform::Identity);
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

}  // namespace lib::scene

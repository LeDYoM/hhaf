#include "scenenode.hpp"
#include "scenemanager.hpp"
#include <haf/system/i_include/get_system.hpp>

using namespace mtps;

namespace haf::scene
{
SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{std::move(name)},
    SceneNodeParent{parent},
    SceneNodes{this},
    Renderizables{this},
    sys::DataWrapperCreator{this},
    ComposedComponentContainer{this},
    sys::SystemAccess{parent != nullptr ? &(parent->isystemProvider())
                                        : nullptr},
    visible{true}
{}

SceneNode::~SceneNode() = default;

void SceneNode::clearAll()
{
    clearSceneNodes();
    clearComponents();
}

}  // namespace haf::scene

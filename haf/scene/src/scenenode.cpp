#include "scenenode.hpp"
#include "scenemanager.hpp"
#include <system/i_include/get_system.hpp>

using namespace mtps;

namespace haf::scene
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
    InterfaceGetter{this},
    SceneNodePropertiesContent()
{
}

SceneNode::~SceneNode() = default;

void SceneNode::clearAll()
{
    clearSceneNodes();
    clearComponents();
}

}  // namespace haf::scene

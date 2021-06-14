#include <haf/include/scene/scenenode.hpp>
#include "scenemanager.hpp"
#include "system/get_system.hpp"

using namespace htps;

namespace haf::scene
{
struct SceneNode::SceneNodePrivate
{
    SceneNodePrivate() = default;
};

SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{std::move(name)},
    SceneNodeParent{parent},
    SceneNodes{this},
    Transformable{},
    sys::DataWrapperCreator{this},
    ComponentContainer{this},
    sys::SystemAccess{parent != nullptr ? &(parent->isystemProvider())
                                        : nullptr},
    InterfaceGetter{this},
    SceneNodeProperties(true),
    p_{make_pimplp<SceneNodePrivate>()}
{}

SceneNode::~SceneNode() = default;

void SceneNode::clearAll()
{
    clearSceneNodes();
    clearComponents();
}

}  // namespace haf::scene

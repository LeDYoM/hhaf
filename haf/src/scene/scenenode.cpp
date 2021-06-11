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
    Renderizables{this},
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

Renderizables& SceneNode::renderizables()
{
    return *this;
}

Renderizables const& SceneNode::renderizables() const
{
    return *this;
}

}  // namespace haf::scene

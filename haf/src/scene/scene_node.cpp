#include <haf/include/scene/scene_node.hpp>

#include <haf/include/scene/scene.hpp>
#include <haf/include/system/datawrappercreator.hpp>

using namespace haf::types;

namespace haf::scene
{
struct SceneNode::SceneNodePrivate
{
    uptr<sys::DataWrapperCreator> subsystems_;
};

SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{std::move(name)},
    SceneNodeParent{std::move(parent)},
    SceneNodes{this},
    sys::SystemAccess{ancestor<Scene>() != nullptr
                          ? &(ancestor<Scene>()->isystemProvider())
                          : nullptr},
    SceneNodeProperties(true),
    component::ComponentContainer{this},
    p_{make_pimplp<SceneNodePrivate>()}
{}

SceneNode::~SceneNode() = default;

void SceneNode::clearAll()
{
    clearSceneNodes();
}

sys::DataWrapperCreator& SceneNode::subsystems()
{
    if (p_->subsystems_ == nullptr)
    {
        p_->subsystems_ = types::muptr<sys::DataWrapperCreator>(this);
    }

    return *(p_->subsystems_);
}

sys::DataWrapperCreator& SceneNode::subsystems() const
{
    return *(p_->subsystems_);
}

}  // namespace haf::scene

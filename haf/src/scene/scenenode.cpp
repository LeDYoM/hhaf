#include <haf/include/scene/scenenode.hpp>

#include <haf/include/scene/componentcontainer.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/system/datawrappercreator.hpp>

using namespace htps;

namespace haf::scene
{
struct SceneNode::SceneNodePrivate
{
    SceneNodePrivate() = default;
    uptr<ComponentContainer> component_container_;
    uptr<sys::DataWrapperCreator> subsystems_;
};

SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{std::move(name)},
    SceneNodeParent{parent},
    SceneNodes{this},
    sys::SystemAccess{ancestor<Scene>() != nullptr
                          ? &(ancestor<Scene>()->isystemProvider())
                          : nullptr},
    SceneNodeProperties(true),
    p_{make_pimplp<SceneNodePrivate>()}
{}

SceneNode::~SceneNode() = default;

void SceneNode::clearAll()
{
    clearSceneNodes();
    // clearComponents();
}

ComponentContainer& SceneNode::components()
{
    if (p_->component_container_ == nullptr)
    {
        p_->component_container_ = muptr<ComponentContainer>(this);
    }

    return *(p_->component_container_);
}

ComponentContainer const& SceneNode::components() const noexcept
{
    return *(p_->component_container_);
}

bool SceneNode::hasComponents() const noexcept
{
    return p_->component_container_ != nullptr;
}

sys::DataWrapperCreator& SceneNode::subsystems()
{
    if (p_->subsystems_ == nullptr)
    {
        p_->subsystems_ = muptr<sys::DataWrapperCreator>(this);
    }

    return *(p_->subsystems_);
}

sys::DataWrapperCreator& SceneNode::subsystems() const
{
    return *(p_->subsystems_);
}

}  // namespace haf::scene

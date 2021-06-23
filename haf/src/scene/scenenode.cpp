#include <haf/include/scene/scenenode.hpp>
#include "scenemanager.hpp"
#include "system/get_system.hpp"

#include <haf/include/scene/componentcontainer.hpp>

using namespace htps;

namespace haf::scene
{
struct SceneNode::SceneNodePrivate
{
    SceneNodePrivate() = default;
    uptr<ComponentContainer> component_container_;
};

SceneNode::SceneNode(rptr<SceneNode> parent, str name) :
    sys::HasName{std::move(name)},
    SceneNodeParent{parent},
    SceneNodes{this},
    sys::DataWrapperCreator{this},
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
    //clearComponents();
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

}  // namespace haf::scene
